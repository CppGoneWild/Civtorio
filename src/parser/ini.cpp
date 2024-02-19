#include "ini.hh"


#include "token.hh"


#include <fstream>
#include <list>




/*******************************************************************************
                                 __               __
                    _   ______ _/ /_  _____      / /_
                   | | / / __ `/ / / / / _ \    / __/
                   | |/ / /_/ / / /_/ /  __/   / /_
                   |___/\__,_/_/\__,_/\___/____\__/
                                         /_____/
*******************************************************************************/




parser::ini::value_t::value_t(location_t const & loc, std::string const & name)
: _name(name)
, _value()
, _location(loc)
{}

parser::ini::value_t::value_t(location_t const & loc,
                              std::string const & name,
                              std::string const & value)
: _name(name)
, _value(value)
, _location(loc)
{}


parser::ini::value_t::value_t(location_t const & loc, std::string && name)
: _name(name)
, _value()
, _location(loc)
{}

parser::ini::value_t::value_t(location_t const & loc, std::string && name, std::string && value)
: _name(name)
, _value(value)
, _location(loc)
{}


std::string const & parser::ini::value_t::name() const
{
	return (_name);
}

std::string const & parser::ini::value_t::value() const
{
	return (_value);
}

parser::location_t const &  parser::ini::value_t::location() const
{
	return (_location);
}




/*******************************************************************************
                                  __  _                 __
                  ________  _____/ /_(_)___  ____      / /_
                 / ___/ _ \/ ___/ __/ / __ \/ __ \    / __/
                (__  )  __/ /__/ /_/ / /_/ / / / /   / /_
               /____/\___/\___/\__/_/\____/_/ /_/____\__/
                                               /_____/
*******************************************************************************/




parser::ini::section_t::section_t(location_t const & loc, std::vector<value_t> const & values)
: _name()
, _values(values)
, _location(loc)
{}

parser::ini::section_t::section_t(location_t const & loc, std::string const & name, std::vector<value_t> const & values)
: _name(name)
, _values(values)
, _location(loc)
{}


parser::ini::section_t::section_t(location_t const & loc, std::vector<value_t> && values)
: _name()
, _values(values)
, _location(loc)
{}

parser::ini::section_t::section_t(location_t const & loc, std::string && name, std::vector<value_t> && values)
: _name(name)
, _values(values)
, _location(loc)
{}


std::string const & parser::ini::section_t::name()
{
	return (_name);
}

std::vector<parser::ini::value_t> const & parser::ini::section_t::values()
{
	return (_values);
}

parser::location_t const & parser::ini::section_t::location()
{
	return (_location);
}










static bool _is_line_empty_so_far(std::vector<parser::token_t> const & in, std::size_t end)
{
	if (end == 0)
		return (true);

	for (std::size_t i = end - 1; i >= 0; --i)
	{
		if (in[i].type() == parser::token_t::EOL)
			return (true);
		if (in[i].type() != parser::token_t::SEPARATOR)
			return (false);
	}

	return (true);
}




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
	auto __append_before_token = [](parser::token_t & main, parser::token_t & t)
	{
		return (parser::token_t(t.token() + main.token(), main.location(), parser::token_t::COMMENT));
	};


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

		// concatenate all until previous EOL
		if (_is_line_empty_so_far(in, i))
		{
			while (tmp.empty() == false && tmp.back().type() != parser::token_t::EOL)
			{
				__append_before_token(comment, tmp.back());
				tmp.pop_back();					
			}
		}

		++i;

		// advance and concatenate until next EOL
		for (; i < in.size() && in[i].type() != parser::token_t::EOL; ++i)
			comment.append(in[i].token());

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
			if (in[i].token() == "\\")
			{
				if (++i < in.size())
					litt.append(in[i++]);
				else
					throw parser::syntax_error("Escaped sequence ill-formed ", litt.location());
				continue;
			}

			if (in[i].token() == "\"")
				break ;

			if (i >= in.size() || 
			    in[i].type() == parser::token_t::COMMENT ||
			    in[i].type() == parser::token_t::EOL)
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



static std::list<std::vector<parser::token_t>> _recreate_line_and_triml(std::vector<parser::token_t> const & in)
{
	std::list<std::vector<parser::token_t>> result;
	std::vector<parser::token_t> current_line;

	for (std::size_t i = 0; i < in.size(); ++i)
	{
		if (in[i].type() != parser::token_t::EOL)
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



static std::vector<parser::token_t> __is_new_section(std::vector<parser::token_t> const & line)
{
	std::vector<parser::token_t> section_name;

	std::list<parser::token_t> tmp(line.cbegin(), line.cend());

	auto __trim_L = [&]()
	{
		while (tmp.size() > 0 && tmp.front().type() == parser::token_t::SEPARATOR)
			tmp.pop_front();
	};

	auto __trim_R = [&]()
	{
		while (tmp.size() > 0 && tmp.back().type() == parser::token_t::SEPARATOR)
			tmp.pop_back();
	};

	__trim_L();
	if (tmp.size() > 0 && tmp.front().token() != "[")
		return (section_name); // Not a section
	tmp.pop_front();
	__trim_L();

	__trim_R();
	if (tmp.back().token() != "]")
		throw ; // Missing ]
	tmp.pop_back();
	__trim_R();

	for (auto it = tmp.begin(); it != tmp.end(); ++it)
	{
		if (it->type() == parser::token_t::SEPARATOR &&
		    (section_name.empty() == false ||
		     section_name.back().type() == parser::token_t::SEPARATOR))
			continue;
		section_name.push_back(*it);
	}

	return (section_name);
}




/*std::vector<section_t>*/ std::vector<parser::token_t>  parser::ini::from_file(std::string const & fname)
{
	std::fstream file;
	//std::vector<parser::ini::section_t> result;
	std::vector<parser::token_t> result;
	location_t loc(fname, 0, 0);

	file.open(fname, std::ios_base::in);

	if (file.is_open() == true)
		result = from_stream(file, loc);
	else
		throw syntax_error("Can't open file", loc);

	return (result);
}


#include <iostream>



/*std::vector<section_t>*/ std::vector<parser::token_t>  parser::ini::from_stream(std::istream & is, location_t & loc)
{
	std::vector<token_t> tokens = tokenize_from_stream(is, loc);

	_remove_comment(tokens);
	_create_litteral(tokens);

	std::list<std::vector<parser::token_t>> lines;

	lines = _recreate_line_and_triml(tokens);

	for (auto it = lines.begin(); it != lines.end(); ++it)
	{
		auto section_name = __is_new_section(*it);
		if (section_name.empty() == false)
			std::cout << "jdfnds3jnfsq3fnj" << std::endl;
	}

	return (tokens);
}
