#ifndef PARSER_AST_HH
#define PARSER_AST_HH



#include "types.hh"


#include <iostream>
#include <string>
#include <vector>



namespace parser
{



struct opt_t
{
	enum comment_style_t
	{
	  C       = 1
	, PreProc = 2

	, All = C | PreProc
	};

	char separator[3] = " \t";

	bool always_keep_new_line = false;
	comment_style_t comment_style = All;

	/*virtual*/ bool is_alpha_num(char) const;
};



class token_t
{
public:
	enum type_t { SEPARATOR, ALPHA_NUM, SPECIAL, EOL };

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



std::vector<token_t> parse_from_file(std::string const &, opt_t const & = opt_t());
std::vector<token_t> parse_from_stream(std::istream &, location_t & loc, opt_t const & = opt_t());



} // parser



#endif // PARSER_AST_HH