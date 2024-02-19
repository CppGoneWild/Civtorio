#ifndef PARSER_INI_HH
#define PARSER_INI_HH


#include "types.hh"
#include "token.hh"


#include <iostream>
#include <string>
#include <vector>


namespace parser
{
namespace ini
{


class value_t
{
public:
	value_t()                = default;
	value_t(value_t const &) = default;
	value_t(value_t &&)      = default;
	~value_t()               = default;

	value_t & operator=(value_t const &) = default;
	value_t & operator=(value_t &&)      = default;

	value_t(location_t const &, std::string const &);
	value_t(location_t const &, std::string const &, std::string const &);

	value_t(location_t const &, std::string &&);
	value_t(location_t const &, std::string &&, std::string &&);

	std::string const & name() const;
	std::string const & value() const;
	location_t const &  location() const;

private:
	std::string _name;
	std::string _value;
	location_t  _location;
};


class section_t
{
public:
	section_t()                  = default;
	section_t(section_t const &) = default;
	section_t(section_t &&)      = default;
	~section_t()                 = default;

	section_t & operator=(section_t const &) = default;
	section_t & operator=(section_t &&)      = default;

	section_t(location_t const &, std::vector<value_t> const &);
	section_t(location_t const &, std::string const &, std::vector<value_t> const &);

	section_t(location_t const &, std::vector<value_t> &&);
	section_t(location_t const &, std::string &&, std::vector<value_t> &&);

	std::string          const & name();
	std::vector<value_t> const & values();
	location_t           const & location();

private:
	std::string          _name;
	std::vector<value_t> _values;
	location_t           _location;
};


/*std::vector<section_t>*/ std::vector<parser::token_t> from_file(std::string const &);
/*std::vector<section_t>*/ std::vector<parser::token_t> from_stream(std::istream &, location_t & loc);

	
} // ini
} // parser


#endif // PARSER_INI_HH