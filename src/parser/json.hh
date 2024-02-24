#ifndef PARSER_JSON_HH
#define PARSER_JSON_HH


#include "types.hh"


#include <iostream>
#include <list>
#include <string>








namespace parser
{
namespace json
{




class element_t
{
public:
	enum type_t { OBJECT, MEMBER, ARRAY, STRING };

	element_t & operator=(element_t const &) = default;
	element_t & operator=(element_t &&)      = default;

	virtual ~element_t() = default;

	virtual type_t type() const = 0;

	location_t const & location() const;
	location_t & location();

	element_t * duplicate() const;

protected:
	element_t()                  = default;
	element_t(element_t const &) = default;
	element_t(element_t &&)      = default;

	explicit element_t(location_t const &);

private:
	location_t _location;	
};








class string_t : public element_t
{
public:
	string_t()                 = default;
	string_t(string_t const &) = default;
	string_t(string_t &&)      = default;
	virtual ~string_t()        = default;

	string_t & operator=(string_t const &) = default;
	string_t & operator=(string_t &&)      = default;

	explicit string_t(std::string const &);
	string_t(std::string const &, location_t const &);

	virtual element_t::type_t type() const override;

	std::string const & value() const;
	std::string & value();

private:
	std::string _value;
};




} // json
} // parser



bool operator==(parser::json::string_t const &, parser::json::string_t const &);
bool operator==(std::string const &, parser::json::string_t const &);
bool operator==(parser::json::string_t const &, std::string const &);

bool operator!=(parser::json::string_t const &, parser::json::string_t const &);
bool operator!=(std::string const &, parser::json::string_t const &);
bool operator!=(parser::json::string_t const &, std::string const &);

bool operator<(parser::json::string_t const &, parser::json::string_t const &);
bool operator<(std::string const &, parser::json::string_t const &);
bool operator<(parser::json::string_t const &, std::string const &);

bool operator>(parser::json::string_t const &, parser::json::string_t const &);
bool operator>(std::string const &, parser::json::string_t const &);
bool operator>(parser::json::string_t const &, std::string const &);

bool operator<=(parser::json::string_t const &, parser::json::string_t const &);
bool operator<=(std::string const &, parser::json::string_t const &);
bool operator<=(parser::json::string_t const &, std::string const &);

bool operator>=(parser::json::string_t const &, parser::json::string_t const &);
bool operator>=(std::string const &, parser::json::string_t const &);
bool operator>=(parser::json::string_t const &, std::string const &);








namespace parser
{
namespace json
{




class member_t : public element_t
{
public:
	member_t() = default;

	explicit member_t(string_t const &, location_t const &);
	member_t(std::string const &, std::string const &);

	member_t(member_t const &);
	member_t(member_t &&);

	member_t & operator=(member_t const &);
	member_t & operator=(member_t &&);

	virtual ~member_t();

	virtual element_t::type_t type() const override;

	string_t const & name() const;
	string_t & name();

	element_t const * value() const;
	element_t * value();
	void set_value(element_t *);

private:
	string_t _name;
	element_t * _value = nullptr;
};




} // json
} // parser




bool operator==(parser::json::member_t const &, parser::json::member_t const &);
bool operator==(std::string const &, parser::json::member_t const &);
bool operator==(parser::json::member_t const &, std::string const &);

bool operator!=(parser::json::member_t const &, parser::json::member_t const &);
bool operator!=(std::string const &, parser::json::member_t const &);
bool operator!=(parser::json::member_t const &, std::string const &);

bool operator<(parser::json::member_t const &, parser::json::member_t const &);
bool operator<(std::string const &, parser::json::member_t const &);
bool operator<(parser::json::member_t const &, std::string const &);

bool operator>(parser::json::member_t const &, parser::json::member_t const &);
bool operator>(std::string const &, parser::json::member_t const &);
bool operator>(parser::json::member_t const &, std::string const &);

bool operator<=(parser::json::member_t const &, parser::json::member_t const &);
bool operator<=(std::string const &, parser::json::member_t const &);
bool operator<=(parser::json::member_t const &, std::string const &);

bool operator>=(parser::json::member_t const &, parser::json::member_t const &);
bool operator>=(std::string const &, parser::json::member_t const &);
bool operator>=(parser::json::member_t const &, std::string const &);








namespace parser
{
namespace json
{






class array_t : public element_t
{
public:
	array_t()                = default;

	explicit array_t(location_t const &);

	array_t(array_t const &);
	array_t(array_t &&);

	array_t & operator=(array_t const &);
	array_t & operator=(array_t &&);

	virtual ~array_t();

	virtual element_t::type_t type() const override;

	std::list<element_t *> const & values() const;
	std::list<element_t *> & values();

private:
	std::list<element_t *> _values;
};








class object_t : public element_t
{
public:
	object_t()                 = default;
	object_t(object_t const &) = default;
	object_t(object_t &&)      = default;
	virtual ~object_t()        = default;

	object_t & operator=(object_t const &) = default;
	object_t & operator=(object_t &&)      = default;

	explicit object_t(location_t const &);

	virtual element_t::type_t type() const override;

	std::list<member_t> const & members() const;
	std::list<member_t> & members();
	void add_members(member_t &);

	member_t const & operator[](std::string const &) const;
	member_t & operator[](std::string const &);

private:
	std::list<member_t> _members;
};








bool from_file(std::string const &, element_t ** result);
bool from_stream(std::istream &, element_t ** result);
bool from_stream(std::istream &, location_t &, element_t ** result);

bool to_file(element_t const &, std::string const &);
bool to_stream(element_t const &, std::istream &);




} // json
} // parser




#endif // PARSER_JSON_HH