#ifndef PARSER_INI_HH
#define PARSER_INI_HH


#include "types.hh"
#include "token.hh"


#include <iostream>
#include <string>
#include <vector>
#include <map>




namespace parser
{
namespace ini
{




class proxy_section_t;
class proxy_value_t;

class const_proxy_section_t;
class const_proxy_value_t;





/*******************************************************************************
                              _____ __         __
                             / __(_) /__      / /_
                            / /_/ / / _ \    / __/
                           / __/ / /  __/   / /_
                          /_/ /_/_/\___/____\__/
                                      /_____/
*******************************************************************************/




class file_t
{
public:
	using values_map_t = std::map<std::string, std::string>;
	using value_t      = values_map_t::value_type;

	using sections_map_t = std::map<std::string, values_map_t>;
	using section_t      = sections_map_t::value_type;

	file_t()               = default;
	file_t(file_t const &) = default;
	file_t(file_t &&)      = default;
	~file_t()              = default;

	file_t & operator=(file_t const &) = default;
	file_t & operator=(file_t &&)      = default;

	explicit file_t(std::string const & filename);
	explicit file_t(std::istream & stream_to_parse);

	bool parse(std::string const & filename);
	bool parse(std::istream & stream_to_parse);
	bool parse(std::istream & stream_to_parse, location_t & loc);

	const_proxy_section_t section(std::string const &) const;
	proxy_section_t section(std::string const &);

	bool add_section(std::string const &);
	bool del_section(std::string const &);
	bool rename_section(std::string const & old, std::string const & newname);

	sections_map_t const & data() const;
	sections_map_t & data();

private:	
	sections_map_t _map;



	friend class const_proxy_section_t;
	friend class const_proxy_value_t;

	friend class proxy_section_t;
	friend class proxy_value_t;
};





/*******************************************************************************
                                                     __  _                 __
    ____  _________  _  ____  __     ________  _____/ /_(_)___  ____      / /_
   / __ \/ ___/ __ \| |/_/ / / /    / ___/ _ \/ ___/ __/ / __ \/ __ \    / __/
  / /_/ / /  / /_/ />  </ /_/ /    (__  )  __/ /__/ /_/ / /_/ / / / /   / /_
 / .___/_/   \____/_/|_|\__, /____/____/\___/\___/\__/_/\____/_/ /_/____\__/
/_/                    /____/_____/                               /_____/
*******************************************************************************/




class proxy_section_t
{
public:
	proxy_section_t()                        = default;
	proxy_section_t(proxy_section_t const &) = default;
	proxy_section_t(proxy_section_t &&)      = default;
	~proxy_section_t()                       = default;

	proxy_section_t & operator=(proxy_section_t const &) = default;
	proxy_section_t & operator=(proxy_section_t &&)      = default;

	proxy_section_t(file_t::section_t &);

	bool is_valid() const;

	std::string const & name();

	const_proxy_value_t value(std::string const &) const;
	proxy_value_t value(std::string const &);

	bool add_value(std::string const &, std::string const & = "");
	bool del_value(std::string const &);
	bool rename_value(std::string const & old, std::string const & newname);

	file_t::values_map_t const & data() const;
	file_t::values_map_t & data();

private:
	file_t::section_t * _section = nullptr;
};




class const_proxy_section_t
{
public:
	const_proxy_section_t()                              = default;
	const_proxy_section_t(const_proxy_section_t const &) = default;
	const_proxy_section_t(const_proxy_section_t &&)      = default;
	~const_proxy_section_t()                             = default;

	const_proxy_section_t & operator=(const_proxy_section_t const &) = default;
	const_proxy_section_t & operator=(const_proxy_section_t &&)      = default;

	const_proxy_section_t(file_t::section_t const &);

	bool is_valid() const;

	std::string const & name();


	const_proxy_value_t value(std::string const &) const;

	file_t::values_map_t const & data() const;

private:
	file_t::section_t const * _section = nullptr;
};




/*******************************************************************************
                                                __               __
    ____  _________  _  ____  __   _   ______ _/ /_  _____      / /_
   / __ \/ ___/ __ \| |/_/ / / /  | | / / __ `/ / / / / _ \    / __/
  / /_/ / /  / /_/ />  </ /_/ /   | |/ / /_/ / / /_/ /  __/   / /_
 / .___/_/   \____/_/|_|\__, /____|___/\__,_/_/\__,_/\___/____\__/
/_/                    /____/_____/                     /_____/
*******************************************************************************/




class proxy_value_t
{
public:
	proxy_value_t()                      = default;
	proxy_value_t(proxy_value_t const &) = default;
	proxy_value_t(proxy_value_t &&)      = default;
	~proxy_value_t()                     = default;

	proxy_value_t & operator=(proxy_value_t const &) = default;
	proxy_value_t & operator=(proxy_value_t &&)      = default;

	proxy_value_t(file_t::value_t &);

	bool is_valid() const;

	std::string const & name() const;

	std::string const & value() const;
	std::string & name();

private:
	file_t::value_t * _value = nullptr;
};


class const_proxy_value_t
{
public:
	const_proxy_value_t()                            = default;
	const_proxy_value_t(const_proxy_value_t const &) = default;
	const_proxy_value_t(const_proxy_value_t &&)      = default;
	~const_proxy_value_t()                           = default;

	const_proxy_value_t & operator=(const_proxy_value_t const &) = default;
	const_proxy_value_t & operator=(const_proxy_value_t &&)      = default;

	const_proxy_value_t(file_t::value_t const &);

	bool is_valid() const;

	std::string const & name() const;

	std::string const & value() const;

private:
	file_t::value_t const * _value = nullptr;
};



	
} // ini
} // parser


#endif // PARSER_INI_HH