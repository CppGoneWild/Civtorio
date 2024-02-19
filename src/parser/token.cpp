#include "token.hh"


#include <fstream>




parser::token_t::token_t(std::string const & t, location_t const & l, type_t tp)
: _location(l)
, _token(t)
, _type(tp)
{}

parser::location_t  const & parser::token_t::location() const
{
	return (_location);
}

std::string const & parser::token_t::token() const
{
	return (_token);
}

parser::token_t::type_t parser::token_t::type() const
{
	return (_type);
}

void parser::token_t::append(std::string const & str)
{
	_token += str;
}

void parser::token_t::append(std::string const & str, location_t const & /*l*/)
{
	_token += str;
	// _location = l;
}

void parser::token_t::append(token_t const & tok)
{
	_token += tok._token;
}



static bool _is_separator(char c)
{
	return (c == ' ' || c == '\t');
}


static bool _is_alphanum(char c)
{
	return ((c >= 'a' && c <= 'z') ||
	        (c >= 'A' && c <= 'Z') ||
	        (c >= '0' && c <= '9') ||
	        c == '_');
}




static parser::token_t _advance_while_separator(std::string const & str, parser::location_t & loc)
{
	parser::location_t result(loc);
	std::string tmp;

	while (loc.column < str.size() && _is_separator(str[loc.column]))
	{
		tmp += str[loc.column];
		++(loc.column);
	}

	return (parser::token_t(tmp, result, parser::token_t::SEPARATOR));
}


static parser::token_t _advance_while_alphanum(std::string const & str, parser::location_t & loc)
{
	parser::location_t result(loc);
	std::string tmp;

	while (loc.column < str.size() &&_is_alphanum(str[loc.column]))
	{
		tmp += str[loc.column];
		++(loc.column);
	}

	return (parser::token_t(tmp, result, parser::token_t::ALPHA_NUM));
}


static parser::token_t _advance_not_alphanum(std::string const & str, parser::location_t & loc)
{
	parser::location_t result(loc);
	std::string tmp;

	tmp += str[loc.column];
	++(loc.column);

	return(parser::token_t(tmp, result, parser::token_t::SPECIAL));
}


static parser::token_t _create_newline_token(parser::location_t & loc)
{
	++(loc.column);
	return(parser::token_t(std::string("\n"), loc, parser::token_t::EOL));
}















std::vector<parser::token_t> parser::tokenize_from_file(std::string const & fname)
{
	std::fstream file;
	std::vector<token_t> result;
	location_t loc(fname, 0, 0);

	file.open(fname, std::ios_base::in);

	if (file.is_open() == true)
		result = tokenize_from_stream(file, loc);
	else
		throw syntax_error("Can't open file", loc);

	return (result);
}





std::vector<parser::token_t> parser::tokenize_from_stream(std::istream & stream,
                                                          location_t & loc)
{
	std::vector<token_t> ast;
	std::string current_line;

	while (stream.good())
	{
		current_line.clear();
		std::getline(stream, current_line); ///< @warning Can blow up memory : should limit read size.
		loc.line += 1;
		loc.column = 0;

		while (loc.column < current_line.size())
		{
			token_t tok = _advance_while_separator(current_line, loc);
			if (tok.token().empty() == false)
				ast.emplace_back(std::move(tok));

			if (loc.column >= current_line.size())
				continue ;

			if (_is_alphanum(current_line[loc.column]))
			{
				token_t tok = _advance_while_alphanum(current_line, loc);
				if (tok.token().empty() == false)
					ast.emplace_back(std::move(tok));
			}
			else
			{
				token_t tok = _advance_not_alphanum(current_line, loc);
				if (tok.token().empty() == false)
					ast.emplace_back(std::move(tok));
			}
		}

		ast.emplace_back(_create_newline_token(loc));
	}

	return (ast);
}

