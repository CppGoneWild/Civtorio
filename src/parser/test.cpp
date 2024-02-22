#include "token.hh"

#include "ini.hh"

#include <iostream>





void test_syntax_error()
{
	parser::syntax_error err1("error origin", parser::location_t("filename", 2, 0));
	parser::syntax_error err2("error intermediare", parser::location_t("filename", 1, 0), std::move(err1));


	std::cout << err2 << std::endl;
}



void test_parser(std::string const & fname)
{
	parser::ini::file_t ini_file;
	ini_file.parse(fname);


	for (auto it_sec = ini_file.data().begin();
	          it_sec != ini_file.data().end();
	          ++it_sec)
	{
		for (auto it_var = it_sec->second.begin();
		          it_var != it_sec->second.end();
		          ++it_var)
		{
			std::cout << "[" << it_sec->first << "]\t" << it_var->first << "\t=\t" << it_var->second << std::endl;
		}
	}
}








int main()
{
	test_syntax_error();

	std::cout << std::endl << std::endl << std::endl << std::endl;

	test_parser("testfile2.ini");

	std::cout << std::endl << std::endl << std::endl << std::endl;

	test_parser("testfile.ini");

  return (0);
}