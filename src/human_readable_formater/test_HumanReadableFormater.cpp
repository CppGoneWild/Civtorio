#include "HumanReadableFormater.hh"


#include <iostream>


int main()
{
	HumanReadableFormater formater;

	formater.default_format_short.nb_digit_after_decimal_sep = 0;
	formater.default_format_short.trail_space_if_positive = true;
	formater.default_format_short.type = HumanReadableFormater::format_short_t::SI;
	formater.default_format_short.print_long_form = true;

	formater.default_format_exact.nb_digit_after_decimal_sep = 9;


/*	std::cout << "-123456789 ->" <<  formater.short_form(-123456789) << std::endl;
	std::cout << "-123456789 ->" <<  formater.exact_form(-123456789) << std::endl;
	std::cout << "0 ->" <<  formater.short_form(0) << std::endl;
	std::cout << "1564252 ->" <<  formater.short_form(1564252) << std::endl;
	std::cout << "3213654324.24354 ->" <<  formater.short_form(3213654324.24354) << std::endl;
	std::cout << "0.2145 ->" <<  formater.short_form(0.2145) << std::endl;
*/

	std::cout << "123 ->" <<  formater.exact_form(123) << std::endl;
	std::cout << "1234 ->" <<  formater.exact_form(1234) << std::endl;
	std::cout << "123456 ->" <<  formater.exact_form(123456) << std::endl;
	std::cout << "1234567 ->" <<  formater.exact_form(1234567) << std::endl;

	std::cout << "0.123 ->" <<  formater.exact_form(0.123) << std::endl;
	std::cout << "0.1234 ->" <<  formater.exact_form(0.1234) << std::endl;
	std::cout << "0.123456 ->" <<  formater.exact_form(0.123456) << std::endl;
	std::cout << "0.1234567 ->" <<  formater.exact_form(0.1234567) << std::endl;

	std::cout << "123.123 ->" <<  formater.exact_form(123.123) << std::endl;
	std::cout << "1234.1234 ->" <<  formater.exact_form(1234.1234) << std::endl;
	std::cout << "123456.123456 ->" <<  formater.exact_form(123456.123456) << std::endl;
	std::cout << "1234567.1234567 ->" <<  formater.exact_form(1234567.1234567) << std::endl;

	return (0);
}