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
	auto print = [](std::vector<parser::token_t> const & v)
	{
		for (auto it = v.cbegin(); it != v.cend(); ++it)
		{
			std::cout << it->location() << "\t\t";

			if (it->type() == parser::token_t::SEPARATOR)
				std::cout << "SEPARATOR" << "\t";
			else if (it->type() == parser::token_t::ALPHA_NUM)
				std::cout << "ALPHA_NUM" << "\t";
			else if (it->type() == parser::token_t::SPECIAL)
				std::cout << "SPECIAL  " << "\t";
			else if (it->type() == parser::token_t::EOL)
				std::cout << "EOL      " << "\t";
			else if (it->type() == parser::token_t::COMMENT)
				std::cout << "COMMENT  " << "\t";
			else if (it->type() == parser::token_t::LITTERAL)
				std::cout << "LITTERAL " << "\t";


			if (it->type() != parser::token_t::EOL)
				std::cout << "\"" << it->token() << "\"" ;
			std::cout << std::endl;
		}
	};



	try
	{
		std::vector<parser::token_t> tmp;
		tmp = parser::ini::from_file(fname);
		print(tmp);
	}
	catch (parser::syntax_error & e)
	{
		std::cout << e << std::endl;
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