#include "json.hh"


#include "token.hh"


#include <algorithm>
#include <fstream>
#include <cassert>








/*******************************************************************************
                      __                          __      __
                ___  / /__  ____ ___  ___  ____  / /_    / /_
               / _ \/ / _ \/ __ `__ \/ _ \/ __ \/ __/   / __/
              /  __/ /  __/ / / / / /  __/ / / / /_    / /_
              \___/_/\___/_/ /_/ /_/\___/_/ /_/\__/____\__/
                                                 /_____/
*******************************************************************************/




parser::json::element_t::element_t(location_t const & l)
: _location(l)
{}

parser::location_t const & parser::json::element_t::location() const
{
	return (_location);
}

parser::location_t & parser::json::element_t::location()
{
	return (_location);
}

parser::json::element_t * parser::json::element_t::duplicate() const
{
	if (type() == parser::json::element_t::OBJECT)
		return (new object_t(*dynamic_cast<object_t const *>(this)));
	else if (type() == parser::json::element_t::MEMBER)
		return (new member_t(*dynamic_cast<member_t const *>(this)));
	else if (type() == parser::json::element_t::ARRAY)
		return (new array_t(*dynamic_cast<array_t const *>(this)));
	else if (type() == parser::json::element_t::STRING)
		return (new string_t(*dynamic_cast<string_t const *>(this)));
	else
		assert(false);
	return (nullptr);
}









/*******************************************************************************
                           __       _                 __
                     _____/ /______(_)___  ____ _    / /_
                    / ___/ __/ ___/ / __ \/ __ `/   / __/
                   (__  ) /_/ /  / / / / / /_/ /   / /_
                  /____/\__/_/  /_/_/ /_/\__, /____\__/
                                        /____/_____/
*******************************************************************************/




parser::json::string_t::string_t(std::string const & v)
: element_t(), _value(v)
{}

parser::json::string_t::string_t(std::string const & v, location_t const & l)
: element_t(l), _value(v)
{}

parser::json::element_t::type_t parser::json::string_t::type() const
{
	return (parser::json::element_t::STRING);
}

std::string const & parser::json::string_t::value() const
{
	return (_value);
}

std::string & parser::json::string_t::value()
{
	return (_value);
}







bool operator==(parser::json::string_t const & lhs, parser::json::string_t const & rhs)
{
	return (lhs.value() == rhs.value());
}

bool operator==(std::string const & lhs, parser::json::string_t const & rhs)
{
	return (lhs == rhs.value());
}

bool operator==(parser::json::string_t const & lhs, std::string const & rhs)
{
	return (lhs.value() == rhs);
}


bool operator!=(parser::json::string_t const & lhs, parser::json::string_t const & rhs)
{
	return (lhs.value() != rhs.value());
}

bool operator!=(std::string const & lhs, parser::json::string_t const & rhs)
{
	return (lhs != rhs.value());
}

bool operator!=(parser::json::string_t const & lhs, std::string const & rhs)
{
	return (lhs.value() != rhs);
}


bool operator<(parser::json::string_t const & lhs, parser::json::string_t const & rhs)
{
	return (lhs.value() < rhs.value());
}

bool operator<(std::string const & lhs, parser::json::string_t const & rhs)
{
	return (lhs < rhs.value());
}

bool operator<(parser::json::string_t const & lhs, std::string const & rhs)
{
	return (lhs.value() < rhs);
}


bool operator>(parser::json::string_t const & lhs, parser::json::string_t const & rhs)
{
	return (lhs.value() > rhs.value());
}

bool operator>(std::string const & lhs, parser::json::string_t const & rhs)
{
	return (lhs > rhs.value());
}

bool operator>(parser::json::string_t const & lhs, std::string const & rhs)
{
	return (lhs.value() > rhs);
}


bool operator<=(parser::json::string_t const & lhs, parser::json::string_t const & rhs)
{
	return (lhs.value() <= rhs.value());
}

bool operator<=(std::string const & lhs, parser::json::string_t const & rhs)
{
	return (lhs <= rhs.value());
}

bool operator<=(parser::json::string_t const & lhs, std::string const & rhs)
{
	return (lhs.value() <= rhs);
}


bool operator>=(parser::json::string_t const & lhs, parser::json::string_t const & rhs)
{
	return (lhs.value() >= rhs.value());
}

bool operator>=(std::string const & lhs, parser::json::string_t const & rhs)
{
	return (lhs >= rhs.value());
}

bool operator>=(parser::json::string_t const & lhs, std::string const & rhs)
{
	return (lhs.value() >= rhs);
}











/*******************************************************************************
                                           __               __
                 ____ ___  ___  ____ ___  / /_  ___  _____ / /_
                / __ `__ \/ _ \/ __ `__ \/ __ \/ _ \/ ___// __/
               / / / / / /  __/ / / / / / /_/ /  __/ /   / /_
              /_/ /_/ /_/\___/_/ /_/ /_/_.___/\___/_/____\__/
                                                   /_____/
*******************************************************************************/




parser::json::member_t::member_t(string_t const & name, location_t const & l)
: element_t(l), _name(name), _value(nullptr)
{}

parser::json::member_t::member_t(std::string const & name, std::string const & val)
: element_t(), _name(string_t(name)), _value(new string_t(val))
{}

parser::json::member_t::member_t(member_t const & oth)
: element_t(oth), _name(oth._name), _value(nullptr)
{
	if (oth.value())
		_value = oth._value->duplicate();
}

parser::json::member_t::member_t(member_t && oth)
: element_t(), _name(oth._name), _value(oth._value)
{
	oth._value = nullptr;
}

parser::json::member_t & parser::json::member_t::operator=(member_t const & oth)
{
	if (this != &oth)
	{
		(*static_cast<element_t *>(this)) = oth;
		_name = oth._name;
		delete _value;
		_value = nullptr;
		if (oth._value)
			_value = oth._value->duplicate();
	}
	return (*this);
}

parser::json::member_t & parser::json::member_t::operator=(member_t && oth)
{
	if (this != &oth)
	{
		(*static_cast<element_t *>(this)) = oth;
		_name = oth._name;
		delete _value;
		_value = oth._value;

		oth._name = string_t();
		oth._value = nullptr;
	}
	return (*this);
}

parser::json::member_t::~member_t()
{
	delete _value;
}

parser::json::element_t::type_t parser::json::member_t::type() const
{
	return (parser::json::element_t::MEMBER);
}

parser::json::string_t const & parser::json::member_t::name() const
{
	return (_name);
}

parser::json::string_t & parser::json::member_t::name()
{
	return (_name);
}

parser::json::element_t const * parser::json::member_t::value() const
{
	return (_value);
}

parser::json::element_t * parser::json::member_t::value()
{
	return (_value);
}

void parser::json::member_t::set_value(element_t * e)
{
	delete _value;
	_value = e;
}







bool operator==(parser::json::member_t const & lhs, parser::json::member_t const & rhs)
{
	return (lhs.name() == rhs.name());
}

bool operator==(std::string const & lhs, parser::json::member_t const & rhs)
{
	return (lhs == rhs.name());
}

bool operator==(parser::json::member_t const & lhs, std::string const & rhs)
{
	return (lhs.name() == rhs);
}


bool operator!=(parser::json::member_t const & lhs, parser::json::member_t const & rhs)
{
	return (lhs.name() != rhs.name());
}

bool operator!=(std::string const & lhs, parser::json::member_t const & rhs)
{
	return (lhs != rhs.name());
}

bool operator!=(parser::json::member_t const & lhs, std::string const & rhs)
{
	return (lhs.name() != rhs);
}


bool operator<(parser::json::member_t const & lhs, parser::json::member_t const & rhs)
{
	return (lhs.name() < rhs.name());
}

bool operator<(std::string const & lhs, parser::json::member_t const & rhs)
{
	return (lhs < rhs.name());
}

bool operator<(parser::json::member_t const & lhs, std::string const & rhs)
{
	return (lhs.name() < rhs);
}


bool operator>(parser::json::member_t const & lhs, parser::json::member_t const & rhs)
{
	return (lhs.name() > rhs.name());
}

bool operator>(std::string const & lhs, parser::json::member_t const & rhs)
{
	return (lhs > rhs.name());
}

bool operator>(parser::json::member_t const & lhs, std::string const & rhs)
{
	return (lhs.name() > rhs);
}


bool operator<=(parser::json::member_t const & lhs, parser::json::member_t const & rhs)
{
	return (lhs.name() <= rhs.name());
}

bool operator<=(std::string const & lhs, parser::json::member_t const & rhs)
{
	return (lhs <= rhs.name());
}

bool operator<=(parser::json::member_t const & lhs, std::string const & rhs)
{
	return (lhs.name() <= rhs);
}


bool operator>=(parser::json::member_t const & lhs, parser::json::member_t const & rhs)
{
	return (lhs.name() >= rhs.name());
}

bool operator>=(std::string const & lhs, parser::json::member_t const & rhs)
{
	return (lhs >= rhs.name());
}

bool operator>=(parser::json::member_t const & lhs, std::string const & rhs)
{
	return (lhs.name() >= rhs);
}









/*******************************************************************************
                                                      __
                     ____ _______________ ___  __    / /_
                    / __ `/ ___/ ___/ __ `/ / / /   / __/
                   / /_/ / /  / /  / /_/ / /_/ /   / /_
                   \__,_/_/  /_/   \__,_/\__, /____\__/
                                        /____/_____/
*******************************************************************************/




parser::json::array_t::array_t(location_t const & l)
: element_t(l), _values()
{}

parser::json::array_t::array_t(array_t const & oth)
: element_t(oth), _values()
{
	for (auto it = oth._values.cbegin(); it != oth._values.cend(); ++it)
		_values.push_back((*it)->duplicate());
}

parser::json::array_t::array_t(array_t && oth)
: element_t(oth), _values(oth._values)
{}

parser::json::array_t & parser::json::array_t::operator=(array_t const & oth)
{
	if (this != &oth)
	{
		(*static_cast<element_t *>(this)) = oth;
		for (auto it = oth._values.cbegin(); it != oth._values.cend(); ++it)
			delete *it;
		_values.clear();
		for (auto it = oth._values.cbegin(); it != oth._values.cend(); ++it)
			_values.push_back((*it)->duplicate());

	}
	return (*this);
}

parser::json::array_t & parser::json::array_t::operator=(array_t && oth)
{
	if (this != &oth)
	{
		(*static_cast<element_t *>(this)) = oth;
		for (auto it = oth._values.cbegin(); it != oth._values.cend(); ++it)
			delete *it;
		_values.clear();
		std::swap(_values, oth._values);
	}
	return (*this);
}

parser::json::array_t::~array_t()
{
	for (auto it = _values.begin(); it != _values.end(); ++it)
		delete *it;
}


parser::json::element_t::type_t parser::json::array_t::type() const
{
	return (parser::json::element_t::ARRAY);
}

std::list<parser::json::element_t *> const & parser::json::array_t::values() const
{
	return (_values);
}

std::list<parser::json::element_t *> & parser::json::array_t::values()
{
	return (_values);
}









/*******************************************************************************
                          __      _           __      __
                   ____  / /_    (_)__  _____/ /_    / /_
                  / __ \/ __ \  / / _ \/ ___/ __/   / __/
                 / /_/ / /_/ / / /  __/ /__/ /_    / /_
                 \____/_.___/_/ /\___/\___/\__/____\__/
                           /___/             /_____/
*******************************************************************************/




parser::json::object_t::object_t(location_t const & l)
: element_t(l)
{}

parser::json::element_t::type_t parser::json::object_t::type() const
{
	return (parser::json::element_t::OBJECT);
}

std::list<parser::json::member_t> const & parser::json::object_t::members() const
{
	return (_members);
}

std::list<parser::json::member_t> & parser::json::object_t::members()
{
	return (_members);
}

void parser::json::object_t::add_members(member_t & m)
{
	auto unary_pred = [&m](member_t const & lm)
	{
		return (lm.name() == m.name());
	};

	std::cout << "Try to add '" << m.name().value() << "'" << std::endl;

	auto found = std::find_if(_members.cbegin(), _members.cend(), unary_pred);
	if (found != _members.cend())
		throw syntax_error("Member already declared.", location_t());


	_members.emplace_back(m);
}

parser::json::member_t const & parser::json::object_t::operator[](std::string const & m) const
{
	auto unary_pred = [&m](member_t const & lm)
	{
		return (lm.name() == m);
	};

	auto found = std::find_if(_members.cbegin(), _members.cend(), unary_pred);
	if (found == _members.cend())
		throw syntax_error("Member already declared.", location_t());
	return (*found);
}

parser::json::member_t & parser::json::object_t::operator[](std::string const & m)
{
	auto unary_pred = [&m](member_t const & lm)
	{
		return (lm.name() == m);
	};

	auto found = std::find_if(_members.begin(), _members.end(), unary_pred);
	if (found == _members.end())
		throw syntax_error("Member already declared.", location_t());
	return (*found);
}









/*******************************************************************************
                         ____
                        / __/________  ____ ___
                       / /_/ ___/ __ \/ __ `__ \
                      / __/ /  / /_/ / / / / / /
                     /_/ /_/   \____/_/ /_/ /_/_____
                                             /_____/
*******************************************************************************/


static bool __is_escaped(std::vector<parser::token_t> const & in, std::size_t i)
{
	if (i == 0)
		return (false);
	if (in[i - 1].token() == "\\" && __is_escaped(in, i - 1) == false)
		return (true);
	return (false);
}






static void __create_litteral(std::vector<parser::token_t> & in)
{
	std::vector<parser::token_t> tmp;

	for (std::size_t i = 0; i < in.size(); ++i)
	{
		if (i > 0 && in[i].token() == "\"" && __is_escaped(in, i) == false)
		{
			++i;
			while (i < in.size() && (in[i].token() == "\"" && __is_escaped(in, i) == false) == false)
			{
				if (tmp.empty())
					tmp.push_back(parser::token_t(in[i].token(), in[i].location(), parser::token_t::LITTERAL));
				else if (tmp.back().type() != parser::token_t::LITTERAL)
					tmp.back() = parser::token_t(tmp.back().token() + in[i].token(), tmp.back().location(), parser::token_t::LITTERAL);
				else
					tmp.back().append(in[i].token());
			}
			++i;
			continue;
		}

		tmp.push_back(in[i]);
	}
	std::swap(tmp, in);
}




static void __remove_multi_line_comment(std::vector<parser::token_t> & in)
{
	std::vector<parser::token_t> tmp;
	bool inside_comment_block = false;

	for (std::size_t i = 0; i < in.size(); ++i)
	{
		if (inside_comment_block)
		{
			if (i > 0 &&
			    in[i].type() != parser::token_t::LITTERAL &&
			    in[i].token() == "/" &&
			    in[i - 1].token() == "*" &&
			    in[i - 1].type() != parser::token_t::LITTERAL &&
			    __is_escaped(in, i - 1) == false)
				inside_comment_block = false;
			continue;
		}
		
		if (i > 0 &&
		    in[i].type() != parser::token_t::LITTERAL &&
		    in[i].token() == "*" &&
		    in[i - 1].token() == "/" &&
		    in[i - 1].type() != parser::token_t::LITTERAL &&
		    __is_escaped(in, i - 1) == false)
		{
			inside_comment_block = true;
			continue;
		}

		tmp.push_back(in[i]);
	}
	std::swap(tmp, in);
}


static void __remove_single_line_comment(std::vector<parser::token_t> & in)
{
	std::vector<parser::token_t> tmp;

	for (std::size_t i = 0; i < in.size(); ++i)
	{
		if (i > 0 &&
		    in[i].type() != parser::token_t::LITTERAL &&
		    in[i].token() == "/" && 
		    in[i - 1].token() == "/" &&
		    in[i - 1].type() != parser::token_t::LITTERAL &&
		    __is_escaped(in, i - 1) == false)
		{
			++i;
			while (i < in.size() &&
			       in[i].type() != parser::token_t::EOL)
				++i;
			continue;
		}

		tmp.push_back(in[i]);
	}
	std::swap(tmp, in);
}

static void __remove_comment(std::vector<parser::token_t> & in)
{
	__remove_multi_line_comment(in);
	__remove_single_line_comment(in);
}

static void __remove_eol_and_separator(std::vector<parser::token_t> & in)
{
	std::vector<parser::token_t> tmp;
	for (std::size_t i = 0; i < in.size(); ++i)
		if (in[i].type() != parser::token_t::SEPARATOR &&
		    in[i].type() != parser::token_t::EOL)
			tmp.push_back(in[i]);
	std::swap(tmp, in);
}



parser::json::element_t * is_member_or_string(std::vector<parser::token_t> & in, std::size_t & i);
parser::json::element_t * is_array(std::vector<parser::token_t> & in, std::size_t & i);


parser::json::element_t * is_object(std::vector<parser::token_t> & in, std::size_t & i)
{
	if (in[i].token() != "{" || in[i].type() == parser::token_t::LITTERAL)
		return (nullptr);

	parser::json::object_t * result = new parser::json::object_t(in[i].location());
	parser::location_t start_loc = in[i].location();
	++i;


	while (i < in.size())
	{
		parser::json::element_t * tmp = is_member_or_string(in, i);

		if (tmp != nullptr)
		{
			try
			{
				result->add_members(*dynamic_cast<parser::json::member_t*>(tmp));
			}
			catch (parser::syntax_error & e)
			{
				delete tmp;
				throw parser::syntax_error("Member already declared", in[i].location());
			}
			delete tmp;
		}
		else if (in[i].token() == "}" && in[i].type() != parser::token_t::LITTERAL)
		{
			++i;
			return (result);
		}
		else if (in[i].token() == "," && in[i].type() != parser::token_t::LITTERAL)
		{
			++i;
		}
		else
		{
			std::string error_str("Unexpected token :'");
			error_str += in[i].token() + "', expect new member or '}'";
			throw parser::syntax_error(error_str, in[i].location());
		}
	}

	delete result;
	throw parser::syntax_error("Missing closing '}", start_loc);
	return (nullptr);
}


parser::json::element_t * is_array(std::vector<parser::token_t> & in, std::size_t & i)
{
	if (in[i].token() != "[" || in[i].type() == parser::token_t::LITTERAL)
		return (nullptr);

	parser::json::array_t * result = new parser::json::array_t(in[i].location());
	parser::location_t start_loc = in[i].location();
	++i;

	while (i < in.size())
	{
		parser::json::element_t * tmp = is_object(in, i);

		if (tmp == nullptr)
			tmp = is_array(in, i);

		if (tmp == nullptr)
			tmp = is_member_or_string(in, i);

		if (tmp != nullptr)
		{
			result->values().push_back(tmp);
		}
		else if (in[i].token() == "]" && in[i].type() != parser::token_t::LITTERAL)
		{
			++i;
			return (result);
		}
		else if (in[i].token() == "," && in[i].type() != parser::token_t::LITTERAL)
		{
			++i;
		}
		else
		{
			std::string error_str("Unexpected token :'");
			error_str += in[i].token() + "', expect new element or ']'";
			throw parser::syntax_error(error_str, in[i].location());
		}
	}

	delete result;
	throw parser::syntax_error("Missing closing ']", start_loc);
	return (nullptr);
}


parser::json::element_t * is_member_or_string(std::vector<parser::token_t> & in, std::size_t & i)
{
	std::vector<parser::token_t> name;
	parser::json::element_t * elem = nullptr;

	for (; i < in.size(); ++i)
	{
		if (in[i].type() != parser::token_t::LITTERAL &&
		    (in[i].token() == "{" || in[i].token() == "}" ||
		     in[i].token() == "[" || in[i].token() == "]" ||
		     in[i].token() == ","))
			break;
		if (in[i].token() == ":" && in[i].type() != parser::token_t::LITTERAL)
		{
			{
				std::cout << "member name :'";
				for (int a = 0; a < name.size(); ++a)
					std::cout << name[a].token();
				std::cout << "'" << std::endl;
			}

			if (name.empty())
				throw parser::syntax_error("Unexpected token ':'. Member must have a name.", in[i].location());

			++i;
			elem = is_object(in, i);

			if (elem == nullptr)
				elem = is_array(in, i);

			if (elem == nullptr)
				elem = is_member_or_string(in, i);

			if (elem == nullptr)
				throw parser::syntax_error(__PRETTY_FUNCTION__, in[i].location());

			break;
		}
		name.push_back(in[i]);
	}

	if (name.empty())
		return (nullptr);

	parser::json::string_t sname(name[0].token(), name[0].location());
	for (std::size_t it = 1; it < name.size(); ++it)
		sname.value() += name[it].token();

	if (elem == nullptr)
		return (new parser::json::string_t(sname));

	std::cout << "member name :'" << sname.value() << "'" << std::endl;

	parser::json::member_t * mmember = new parser::json::member_t(sname, sname.location());
	mmember->set_value(elem);

	return (mmember);
}








bool parser::json::from_file(std::string const & fname, element_t ** result)
{
	assert(result);
	assert(*result == nullptr);

	bool res = false;

	std::fstream file;
	file.open(fname, std::ios_base::in);

	location_t loc(fname, 0, 0);

	try
	{
		if (file.is_open() == true)
			res = from_stream(file, loc, result);
		else
			throw parser::syntax_error("Can't open file", loc);
	}
	catch (syntax_error & e)
	{
		delete *result;
		*result = nullptr;
		std::cout << e << std::endl;
		res = false;
	}

	return (res);
}

bool parser::json::from_stream(std::istream & is, element_t ** result)
{
	location_t loc("", 0, 0);
	return (from_stream(is, loc, result));
}

bool parser::json::from_stream(std::istream & is, location_t & loc, element_t ** result)
{
	assert(result);
	assert(*result == nullptr);

	bool res = false;


	try
	{
		std::vector<token_t> tokens = tokenize_from_stream(is, loc);

		__create_litteral(tokens);
		__remove_comment(tokens);
		__remove_eol_and_separator(tokens);

		std::size_t i = 0;
		element_t * tmp = nullptr;
		tmp = is_object(tokens, i);

		if (tmp == nullptr)
			tmp = is_array(tokens, i);

		if (tmp == nullptr)
			tmp = is_member_or_string(tokens, i);

		if (tmp != nullptr)
			*result = tmp;
		//else
		//	result = element_t();

		res = true;
	}
	catch (syntax_error & e)
	{
		delete *result;
		*result = nullptr;
		std::cout << e << std::endl;
		res = false;
	}

	return (res);
}











/*******************************************************************************
                                   __
                                  / /_____
                                 / __/ __ \
                                / /_/ /_/ /
                                \__/\____/_____
                                        /_____/
*******************************************************************************/

bool parser::json::to_file(element_t const & e, std::string const & fname)
{
	bool result = false;

	std::fstream file;
	file.open(fname, std::ios_base::out);

	try
	{
		if (file.is_open() == true)
			result = to_stream(e, file);
		else
			throw parser::syntax_error("Can't open file", location_t(fname, 0, 0));
	}
	catch (syntax_error & e)
	{
		std::cout << e << std::endl;
		result = false;
	}

	return (result);
}

bool parser::json::to_stream(element_t const & e, std::istream & is)
{
	return (false);
}
