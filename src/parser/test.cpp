#include "token.hh"













#include <iostream>

int main()
{
	std::vector<parser::token_t> tmp;

	auto print = [](std::vector<parser::token_t> const & v)
	{
		for (auto it = v.cbegin(); it != v.cend(); ++it)
		{
			std::cout << it->location() << "\t\t";

			if (it->type() == parser::token_t::EOL)
				std::cout << "EOL";
			else
				std::cout << "\"" << it->token() << "\"" ;
			std::cout << std::endl;
		}
	};


	try
	{
		tmp = parser::tokenize_from_file("testfile2.ini");
		print(tmp);
		std::cout << std::endl << std::endl << std::endl << std::endl;
		tmp = parser::tokenize_from_file("testfile.ini");
		print(tmp);
	}
	catch (parser::syntax_error & e)
	{
		std::cout << e << std::endl;
	}







  return (0);
}