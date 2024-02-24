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



void test_parser_json(std::string const & fname)
{
	parser::json::element_t * elem = nullptr;

	if (parser::json::from_file(fname, &elem))
	{
		// ini_file.write(std::cout);
		std::cout << "OK" << std::endl;

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