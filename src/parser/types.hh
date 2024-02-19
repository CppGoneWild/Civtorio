#ifndef PARSER_TYPES_HH
#define PARSER_TYPES_HH



#include <string>
#include <vector>

#include <iostream>



namespace parser
{



struct location_t
{
	location_t()                   = default;
	location_t(location_t const &) = default;
	location_t(location_t &&)      = default;
	~location_t()                  = default;

	location_t & operator=(location_t const &) = default;
	location_t & operator=(location_t &&)      = default;

	explicit location_t(std::size_t line);
	location_t(std::size_t line, std::size_t col);
	location_t(std::string const & filename, std::size_t line, std::size_t col);

	std::string filename;
	std::size_t line   = 0;
	std::size_t column = 0;
};



struct syntax_error
{
	syntax_error()                     = default;
	syntax_error(syntax_error const &) = default;
	syntax_error(syntax_error &&)      = default;
	~syntax_error()                    = default;

	syntax_error & operator=(syntax_error const &) = default;
	syntax_error & operator=(syntax_error &&)      = default;

	syntax_error(std::string const & error_str, location_t const & location);
	syntax_error(std::string && error_str, location_t&& location);
	syntax_error(std::string const & error_str, location_t const & location, syntax_error && inner);

	location_t                location;
	std::string               error_str;	

	std::vector<syntax_error> inner_errors;
};



} // parser



std::ostream & operator<<(std::ostream &, parser::location_t const &);
std::ostream & operator<<(std::ostream &, parser::syntax_error const &);



#endif // PARSER_TYPES_HH