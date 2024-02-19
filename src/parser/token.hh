#ifndef PARSER_TOKEN_HH
#define PARSER_TOKEN_HH


#include "types.hh"


#include <iostream>
#include <string>
#include <vector>




namespace parser
{




class token_t
{
public:
	enum type_t { SEPARATOR, ALPHA_NUM, SPECIAL, EOL, COMMENT };

	token_t()               = default;
	token_t(token_t const &) = default;
	token_t(token_t &&)      = default;
	~token_t()              = default;

	token_t & operator=(token_t const &) = default;
	token_t & operator=(token_t &&)        = default;

	token_t(std::string const &, location_t const &, type_t);

	location_t  const & location() const;
	std::string const & token() const;
	type_t type() const;

	void append(std::string const &);
	void append(std::string const &, location_t const &);
	void append(token_t const &);


private:
	location_t _location;
	std::string _token;
	type_t _type;
};




std::vector<token_t> tokenize_from_file(std::string const &);
std::vector<token_t> tokenize_from_stream(std::istream &, location_t & loc);




} // parser


#endif // PARSER_TOKEN_HH