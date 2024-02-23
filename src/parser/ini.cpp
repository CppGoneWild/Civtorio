#include "ini.hh"


#include "token.hh"


#include <iostream>
#include <fstream>
#include <list>
#include <cassert>




/*******************************************************************************
                     ____                  _
                    / __ \____ ___________(_)___  ____ _
                   / /_/ / __ `/ ___/ ___/ / __ \/ __ `/
                  / ____/ /_/ / /  (__  ) / / / / /_/ /
                 /_/    \__,_/_/  /____/_/_/ /_/\__, /
                                               /____/
*******************************************************************************/








static void _concatenate_double_diese(std::vector<parser::token_t> & in)
{
	std::vector<parser::token_t> tmp;
	for (std::size_t i = 0; i < in.size(); ++i)
	{
		if (in[i].token() == "#" &&
		    (tmp.empty() == false && tmp.back().token() == "#"))
			tmp.back().append("#");
		else
			tmp.push_back(in[i]);
	}
	std::swap(tmp, in);
}



static void _remove_comment(std::vector<parser::token_t> & in)
{
	_concatenate_double_diese(in);


	std::vector<parser::token_t> tmp;
	std::size_t i = 0;
	while (i < in.size())
	{
		if (in[i].token() != "##")
		{
			tmp.push_back(in[i++]);
			continue;
		}

		// create comment token
		parser::token_t comment(in[i].token(), in[i].location(), parser::token_t::COMMENT);

		++i;

		// advance and concatenate until next EOL
		for (; i < in.size() /*&& in[i].type() != parser::token_t::EOL*/; ++i)
			comment.append(in[i].token());

		// std::cout << "Comment found " << comment.location() << " : '" << comment.token() << "'" << std::endl;
		// discard comment
		// tmp.push_back(comment);
	}

	std::swap(tmp, in);
}




static void _create_litteral(std::vector<parser::token_t> & in)
{
	std::vector<parser::token_t> tmp;
	std::size_t i = 0;

	while (i < in.size())
	{
		if (in[i].token() != "\"")
		{
			tmp.push_back(in[i++]);
			continue;
		}

		parser::token_t litt("", in[i].location(), parser::token_t::LITTERAL);
		++i;

		for (;;)
		{
			// if (in[i].token() == "\\")
			// {
			// 	if (++i < in.size())
			// 		litt.append(in[i++]);
			// 	else
			// 		throw parser::syntax_error("Escaped sequence ill-formed ", litt.location());
			// 	continue;
			// }

			if (in[i].token() == "\"")
				break ;

			if (i >= in.size()
			    /*|| in[i].type() == parser::token_t::COMMENT*/
			    /*|| in[i].type() == parser::token_t::EOL*/)
			{
				throw parser::syntax_error("Litteral string ill-formed ", litt.location(),
				                           parser::syntax_error("Missing closing '\"'", in[i].location()));
			}
			litt.append(in[i++].token());
		}

		++i;
		tmp.push_back(litt);
	}

	std::swap(tmp, in);
}







static bool __is_token_escaped(std::vector<parser::token_t> const & in, std::size_t i)
{
	if (i == 0)
		return (false);
	if (in[i - 1].token() == "\\" && __is_token_escaped(in, i - 1) == false)
		return (true);
	return (false);
}


static std::list<std::vector<parser::token_t>> _recreate_line_and_triml(std::vector<parser::token_t> const & in)
{
	std::list<std::vector<parser::token_t>> result;
	std::vector<parser::token_t> current_line;

	for (std::size_t i = 0; i < in.size(); ++i)
	{
		if (in[i].type() != parser::token_t::EOL || __is_token_escaped(in, i))
		{
			if ((in[i].type() == parser::token_t::SEPARATOR && current_line.empty()) == false)
				current_line.emplace_back(in[i]);
			continue ;
		}

		if (current_line.empty() == false)
			result.emplace_back(std::move(current_line));
		current_line.clear();
	}

	return (result);
}




static void __trim_R(std::string & str)
{
	while (str.size() > 0 && (str.back() == ' ' || str.back() == '\t'))
		str.pop_back();
}




static bool __is_new_section(std::vector<parser::token_t> const & in, std::string & result)
{
	std::string sname;
	bool scope_found = false;
	std::size_t scope_idx = 0;

	for (std::size_t i = 0; i < in.size(); ++i)
	{
		if (in[i].token() == "[")
		{
			if (scope_found == true)
				throw parser::syntax_error("Unexpected '[' token found.", in[i].location());
			scope_found = true;
			scope_idx = i;
			continue;
		}
		
		if (in[i].token() == "]")
		{
			if (scope_found == false)
				throw parser::syntax_error("Unexpected '[' token found.", in[i].location());
			///@warning check rest of line
			__trim_R(sname);
			result = sname;
			return (true);
		}
		
		if (in[i].type() == parser::token_t::SEPARATOR)
		{
			if (scope_found == false || sname.empty())
				continue;
		}

		sname += in[i].token();
	}

	if (scope_found == true)
		throw parser::syntax_error("Corresponding ']' token not found.", in[scope_idx].location());

	return (false);
}




static bool __is_new_value(std::vector<parser::token_t> const & in,
                           std::string & vname, std::string & vvalue)
{
	std::string *current_target = &vname;
	std::size_t equal_idx = 0;

	for (std::size_t i = 0; i < in.size(); ++i)
	{
		if (in[i].token() == "=")
		{
			if (current_target == &vvalue || vname.empty())
				throw parser::syntax_error("Unexpected token '='", in[i].location());

			current_target = &vvalue;
			equal_idx = i;
			continue;
		}

		if (in[i].type() == parser::token_t::SEPARATOR && current_target->empty())
			continue;

		*current_target += in[i].token();
	}

	if (current_target == &vvalue && vvalue.empty())
		throw parser::syntax_error("Variable with token '=' has no value", in[equal_idx].location());

	__trim_R(vname);
	return (vname.empty() == false);
}







/*******************************************************************************
                              _____ __         __
                             / __(_) /__      / /_
                            / /_/ / / _ \    / __/
                           / __/ / /  __/   / /_
                          /_/ /_/_/\___/____\__/
                                      /_____/
*******************************************************************************/




parser::ini::file_t::file_t(std::string const & filename)
: _map()
{
	bool result = parse(filename);
	assert(result);
}

parser::ini::file_t::file_t(std::istream & stream_to_parse)
: _map()
{
	bool result = parse(stream_to_parse);
	assert(result);
}




bool parser::ini::file_t::parse(std::string const & fname)
{
	bool result = false;

	std::fstream file;
	file.open(fname, std::ios_base::in);

	location_t loc(fname, 0, 0);

	try
	{
		if (file.is_open() == true)
			result = parse(file, loc);
		else
			throw syntax_error("Can't open file", loc);
	}
	catch (syntax_error & e)
	{
		std::cout << e << std::endl;
		result = false;
	}

	return (result);
}


bool parser::ini::file_t::parse(std::istream & stream_to_parse)
{
	location_t loc("", 0, 0);
	return (parse(stream_to_parse, loc));
}


bool parser::ini::file_t::parse(std::istream & stream_to_parse, location_t & loc)
{
	bool result = false;
	std::string current_section_name;

	try
	{
		std::vector<token_t> tokens = tokenize_from_stream(stream_to_parse, loc);
		std::list<std::vector<parser::token_t>> lines = _recreate_line_and_triml(tokens);

		for (auto it_line = lines.begin(); it_line != lines.end(); ++it_line)
		{
			_remove_comment(*it_line);
			_create_litteral(*it_line);
			if (__is_new_section(*it_line, current_section_name))
			{
				auto found = _map.find(current_section_name);
				if (found != _map.end())
					throw syntax_error("Section already declared", (*it_line)[0].location());
				found = _map.insert(section_t(current_section_name, values_map_t())).first;
				continue;
			}

			{
				std::string var_name, var_value;
				if (__is_new_value(*it_line, var_name, var_value))
				{
					auto & tmp = _map[current_section_name];
					auto found = tmp.find(var_name);
					if (found != tmp.end())
						throw syntax_error("Variable already declared", (*it_line)[0].location());
					found = tmp.insert(value_t(var_name, var_value)).first;
				}
			}
		}


		result = true;
	}
	catch (syntax_error & e)
	{
		std::cout << e << std::endl;
		result = false;
	}

	return (result);
}





bool parser::ini::file_t::write(std::string const & fname)
{
	bool result = false;

	std::fstream file;
	file.open(fname, std::ios_base::out);

	if (file.is_open() == true)
		result = write(file);

	return (result);
}




bool parser::ini::file_t::write(std::ostream & os)
{
	for (auto it_sec = _map.cbegin();
	          it_sec != _map.cend();
	          ++it_sec)
	{
		if (it_sec->first.empty() == false)
			os << "[" << it_sec->first << "]" << std::endl;

		for (auto it_var = it_sec->second.cbegin();
		          it_var != it_sec->second.cend();
		          ++it_var)
		{
			if (it_sec->first.empty() == false)
				os << "\t";
			os << it_var->first << "=" << it_var->second << std::endl;
		}
	}

	return (true);
}




parser::ini::const_proxy_section_t parser::ini::file_t::section(std::string const & sname) const
{
	auto found = _map.find(sname);
	if (found != _map.cend())
		return (const_proxy_section_t(*found));
	return (const_proxy_section_t());
}

parser::ini::proxy_section_t parser::ini::file_t::section(std::string const & sname)
{
	auto found = _map.find(sname);
	if (found != _map.end())
		return (proxy_section_t(*found));
	return (proxy_section_t());
}




bool parser::ini::file_t::add_section(std::string const & sname)
{
	auto found = _map.find(sname);
	if (found != _map.end())
		return (false);

	_map.insert(section_t{sname, values_map_t()});
	return (true);
}

bool parser::ini::file_t::del_section(std::string const & sname)
{
	auto found = _map.find(sname);
	if (found != _map.end())
	{
		_map.erase(found);
		return (true);
	}
	return (false);
}

bool parser::ini::file_t::rename_section(std::string const & old, std::string const & newname)
{
	auto found = _map.find(old);
	if (found != _map.end())
		return (false);

	section_t tmp(newname, values_map_t());
	tmp.second = std::move(found->second);

	_map.erase(found);
	_map.insert(tmp);
	return (true);
}




parser::ini::file_t::sections_map_t const & parser::ini::file_t::data() const
{
	return (_map);
}

parser::ini::file_t::sections_map_t & parser::ini::file_t::data()
{
	return (_map);
}




/*******************************************************************************
                                                     __  _                 __
    ____  _________  _  ____  __     ________  _____/ /_(_)___  ____      / /_
   / __ \/ ___/ __ \| |/_/ / / /    / ___/ _ \/ ___/ __/ / __ \/ __ \    / __/
  / /_/ / /  / /_/ />  </ /_/ /    (__  )  __/ /__/ /_/ / /_/ / / / /   / /_
 / .___/_/   \____/_/|_|\__, /____/____/\___/\___/\__/_/\____/_/ /_/____\__/
/_/                    /____/_____/                               /_____/
*******************************************************************************/








parser::ini::proxy_section_t::proxy_section_t(file_t::section_t & s)
: _section(&s)
{}

bool parser::ini::proxy_section_t::is_valid() const
{
	return (_section);
}

std::string const & parser::ini::proxy_section_t::name()
{
	return (_section->first);
}




parser::ini::const_proxy_value_t parser::ini::proxy_section_t::value(std::string const & name) const
{
	auto found = _section->second.find(name);
	if (found != _section->second.cend())
		return (const_proxy_value_t(*found));
	return (const_proxy_value_t());
}

parser::ini::proxy_value_t parser::ini::proxy_section_t::value(std::string const & name)
{
	auto found = _section->second.find(name);
	if (found != _section->second.end())
		return (proxy_value_t(*found));
	return (proxy_value_t());
}




bool parser::ini::proxy_section_t::add_value(std::string const & sname, std::string const & val)
{
	auto found = _section->second.find(sname);
	if (found != _section->second.end())
		return (false);

	_section->second.insert(file_t::value_t(sname, val));

	return (true);
}

bool parser::ini::proxy_section_t::del_value(std::string const & sname)
{
	auto found = _section->second.find(sname);
	if (found != _section->second.end())
	{
		_section->second.erase(found);
		return (true);
	}

	return (false);
}

bool parser::ini::proxy_section_t::rename_value(std::string const & old, std::string const & newname)
{
	auto found = _section->second.find(old);
	if (found != _section->second.end())
	{
		file_t::value_t tmp(newname, std::string());
		tmp.second = std::move(found->second);

		_section->second.erase(found);
		_section->second.insert(tmp);
		return (true);
	}
	return (false);
}




parser::ini::file_t::values_map_t const & parser::ini::proxy_section_t::data() const
{
	return (_section->second);
}

parser::ini::file_t::values_map_t & parser::ini::proxy_section_t::data()
{
	return (_section->second);
}








parser::ini::const_proxy_section_t::const_proxy_section_t(file_t::section_t const & s)
: _section(&s)
{}

bool parser::ini::const_proxy_section_t::is_valid() const
{
	return (_section);
}

std::string const & parser::ini::const_proxy_section_t::name()
{
	return (_section->first);
}

parser::ini::const_proxy_value_t parser::ini::const_proxy_section_t::value(std::string const & vname) const
{
	auto found = _section->second.find(vname);
	if (found != _section->second.cend())
		return (const_proxy_value_t(*found));
	return (const_proxy_value_t());
}

parser::ini::file_t::values_map_t const & parser::ini::const_proxy_section_t::data() const
{
	return (_section->second);
}








/*******************************************************************************
                                                __               __
    ____  _________  _  ____  __   _   ______ _/ /_  _____      / /_
   / __ \/ ___/ __ \| |/_/ / / /  | | / / __ `/ / / / / _ \    / __/
  / /_/ / /  / /_/ />  </ /_/ /   | |/ / /_/ / / /_/ /  __/   / /_
 / .___/_/   \____/_/|_|\__, /____|___/\__,_/_/\__,_/\___/____\__/
/_/                    /____/_____/                     /_____/
*******************************************************************************/








parser::ini::proxy_value_t::proxy_value_t(file_t::value_t & v)
: _value(&v)
{}

bool parser::ini::proxy_value_t::is_valid() const
{
	return (_value);
}

std::string const & parser::ini::proxy_value_t::name() const
{
	return (_value->first);
}

std::string const & parser::ini::proxy_value_t::value() const
{
	return (_value->second);
}

std::string & parser::ini::proxy_value_t::name()
{
	return (_value->second);
}




parser::ini::const_proxy_value_t::const_proxy_value_t(file_t::value_t const & v)
: _value(&v)
{}

bool parser::ini::const_proxy_value_t::is_valid() const
{
	return (_value);
}

std::string const & parser::ini::const_proxy_value_t::name() const
{
	return (_value->first);
}

std::string const & parser::ini::const_proxy_value_t::value() const
{
	return (_value->second);
}
