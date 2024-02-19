#include "ini.hh"


#include "token.hh"


#include <fstream>




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


parser::ini::value_t::value_t(location_t const & loc, std::string &&)
{}

parser::ini::value_t::value_t(location_t const & loc, std::string &&, std::string &&)
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




parser::ini::section_t::section_t(location_t const &, std::vector<value_t> const &)
: _name()
, _values()
, _location()
{}

parser::ini::section_t::section_t(location_t const &, std::string const &, std::vector<value_t> const &)
: _name()
, _values()
, _location()
{}


parser::ini::section_t::section_t(location_t const &, std::vector<value_t> &&)
{}

parser::ini::section_t::section_t(location_t const &, std::string &&, std::vector<value_t> &&)
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

		tmp.push_back(comment);
	}

	std::swap(tmp, in);
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




/*std::vector<section_t>*/ std::vector<parser::token_t>  parser::ini::from_stream(std::istream & is, location_t & loc)
{
	std::vector<token_t> tokens = tokenize_from_stream(is, loc);

	_remove_comment(tokens);

	return (tokens);
}
