#include "token.hh"

#include "ini.hh"
#include "json.hh"

#include <iostream>





void test_syntax_error()
{
	parser::syntax_error err1("error origin", parser::location_t("filename", 2, 0));
	parser::syntax_error err2("error intermediare", parser::location_t("filename", 1, 0), std::move(err1));


	std::cout << err2 << std::endl;
}



void test_parser_ini(std::string const & fname)
{
	parser::ini::file_t ini_file;
	ini_file.parse(fname);

	ini_file.write(std::cout);
}



void print_elem(parser::json::element_t const & obj);

void print_member_or_string(parser::json::element_t const & elem)
{
	if (elem.type() == parser::json::element_t::STRING)
	{
		parser::json::string_t const & str = (*dynamic_cast<parser::json::string_t const*>(&elem));
		std::cout << str.value();
		std::cout << " // String " << str.location() << std::endl;
	}
	else if (elem.type() == parser::json::element_t::MEMBER)
	{
		parser::json::member_t const & mbr = (*dynamic_cast<parser::json::member_t const*>(&elem));
		std::cout << "/*Member*/ " << mbr.name().value() << ":";
		if (mbr.value())
			print_elem(*mbr.value());
	}
	else
		std::cout << "Unknown type at " << elem.location() << std::endl;
}

void print_array(parser::json::array_t const & arr)
{
	std::cout << "// Array " << arr.location() << std::endl;

	std::cout << "[" << std::endl;

	for (auto it = arr.values().cbegin(); it != arr.values().cend(); ++it)
		print_elem(**it);
	std::cout << "]" << std::endl;
}

void print_object(parser::json::object_t const & obj)
{
	std::cout << "// Object " << obj.location() << std::endl;

	std::cout << "{" << std::endl;
	for (auto it = obj.members().cbegin(); it != obj.members().cend(); ++it)
		print_member_or_string(*it);
	std::cout << "}" << std::endl;
}

void print_elem(parser::json::element_t const & elem)
{
	if (elem.type() == parser::json::element_t::OBJECT)
		print_object(*dynamic_cast<parser::json::object_t const*>(&elem));
	else if (elem.type() == parser::json::element_t::ARRAY)
		print_array(*dynamic_cast<parser::json::array_t const*>(&elem));
	else
		print_member_or_string(elem);
}



void test_parser_json(std::string const & fname)
{
	parser::json::element_t * elem = nullptr;

	if (parser::json::from_file(fname, &elem))
	{
		print_elem(*elem);
		delete elem;
		return ;
	}
	std::cout << "KO" << std::endl;
}








int main()
{
//	test_syntax_error();

//	std::cout << std::endl << std::endl << std::endl << std::endl;

//	test_parser_ini("testfile2.ini");

//	std::cout << std::endl << std::endl << std::endl << std::endl;

//	test_parser_ini("testfile.ini");

//	std::cout << std::endl << std::endl << std::endl << std::endl;

	test_parser_json("testfile.json");

  return (0);
}