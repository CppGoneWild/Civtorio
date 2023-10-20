#include "HumanReadableFormater.hh"

#include <cstring>
#include <array>
#include <cmath>
#include <cassert>








static void __print_sign(std::string & result, bool is_neg, HumanReadableFormater::format_t const & format)
{
	if (is_neg)
		result += '-';
	else if (format.always_sign_char)
		result += '+';
	else if (format.trail_space_if_positive)
		result += ' ';
}


static void __print_fractional_part(std::string & result, double fractional_part, HumanReadableFormater::format_t const & format)
{
	if (format.nb_digit_after_decimal_sep > 0)
	{
		fractional_part *= std::pow(10, format.nb_digit_after_decimal_sep);
		unsigned int fractional_part_to_print = static_cast<unsigned int>(fractional_part);
		if (fractional_part_to_print > 0)
		{
			result += format.decimal_separator;
			result += std::to_string(fractional_part_to_print);
		}
	}
}







struct PowerOfTenName
{
	char long_string[9];
	char short_string[3];
	int power_nbr;
	double ref_value; // equal to 10^power_nbr

	PowerOfTenName(std::string const & l, std::string const & s, int p)
	: long_string(), short_string(), power_nbr(p), ref_value(std::pow(10., (double(p))))
	{
		std::strncpy(long_string, l.c_str(), sizeof(long_string));
		std::strncpy(short_string, s.c_str(), sizeof(short_string));
	}
};








static PowerOfTenName const & __find_power_of_ten(double value, HumanReadableFormater::format_short_t const & format)
{
	static const int max_digit_to_display = 3;

	static const std::array<PowerOfTenName, 7> data_si =
	{
		PowerOfTenName{"",       "", 0},
		PowerOfTenName{"kilo",  "k", 3},
		PowerOfTenName{"mega",  "M", 6},
		PowerOfTenName{"giga",  "G", 9},
		PowerOfTenName{"tera",  "T", 12},
		PowerOfTenName{"peta",  "P", 15},
		PowerOfTenName{"exa",   "E", 18}
	};

	static const std::array<PowerOfTenName, 5> data_monetary =
	{
		PowerOfTenName{"",            "",  0},
		PowerOfTenName{"thousand",    "k", 3},
		PowerOfTenName{"million",     "m", 6},
		PowerOfTenName{"billion",     "B", 9},
		PowerOfTenName{"trillion",    "T", 12}
	};

	static const std::array<PowerOfTenName, 5> data_mass =
	{
		PowerOfTenName{"",            "",   0},
		PowerOfTenName{"kilo",        "k",  3},
		PowerOfTenName{"ton",         "t",  6},
		PowerOfTenName{"kiloton",     "kt", 9},
		PowerOfTenName{"megaton",     "Mt", 12}
	};


	PowerOfTenName const * data = nullptr;
	std::size_t data_size = 0;
	if (format.type == HumanReadableFormater::format_short_t::SI)
	{
		data = data_si.data();
		data_size = data_si.size();
	}
	else if (format.type == HumanReadableFormater::format_short_t::MONETARY)
	{
		data = data_monetary.data();
		data_size = data_monetary.size();
	}
	else if (format.type == HumanReadableFormater::format_short_t::MASS)
	{
		data = data_mass.data();
		data_size = data_mass.size();
	}

	assert(data && data_size);

	const int nb_digit = std::floor(std::log10(value) + 1);


	std::size_t i;
	for (i = 0; i < data_size - 1; ++i)
	{
		if (nb_digit - data[i].power_nbr <= max_digit_to_display)
			break;
	}

	return (data[i]);
}




std::string HumanReadableFormater::short_form(double value, format_short_t const & format) const
{
	const bool is_neg = (value < 0.);
	if (is_neg)
		value *= -1.0;

	std::string result;

	__print_sign(result, is_neg, format);

	PowerOfTenName const & data = __find_power_of_ten(value, format);

	value /= data.ref_value;

	double integer_part;
	double fractional_part = std::modf(value, &integer_part);

	result += std::to_string(static_cast<unsigned int>(integer_part));

	if (integer_part < 10. && format.auto_nb_digit && format.nb_digit_after_decimal_sep == 0)
	{
		format_short_t tmp(format);
		tmp.nb_digit_after_decimal_sep = 1;
		__print_fractional_part(result, fractional_part, tmp);
	}
	else
	{
		__print_fractional_part(result, fractional_part, format);
	}


	if ((format.print_long_form && data.long_string[0]) ||
	    (format.print_long_form == false && data.short_string[0]))
	{
		if (format.space_after_number)
			result += ' ';
		if (format.print_long_form)
			result += data.long_string;
		else
			result += data.short_string;
	}

	return (result);
}









static std::string __print_exact_and_simple(double value, HumanReadableFormater::format_exact_t const & format)
{
	double integer_part;
	double fractional_part = std::modf(value, &integer_part);

	std::string result;

	result += std::to_string(static_cast<unsigned int>(integer_part));

	__print_fractional_part(result, fractional_part, format);

	return (result);
}




static std::string __print_exact_and_complex(double value, HumanReadableFormater::format_exact_t const & format)
{
	double integer_part;
	double fractional_part = std::modf(value, &integer_part);

	std::string result;

	{	
		std::string tmp = std::to_string(static_cast<unsigned int>(integer_part));
		std::string reversed_result;
		std::size_t printed = 0;
		for (auto it = tmp.crbegin(); it != tmp.crend(); ++it, ++printed)
		{
			if (printed && printed % 3 == 0)
				reversed_result += format.thousand_separator;
			reversed_result += *it;
		}
		result.append(reversed_result.crbegin(), reversed_result.crend());
	}


	if (format.nb_digit_after_decimal_sep > 0)
	{
		fractional_part *= std::pow(10, format.nb_digit_after_decimal_sep);
		unsigned int fractional_part_to_print = static_cast<unsigned int>(fractional_part);
		if (fractional_part_to_print > 0)
		{
			result += format.decimal_separator;

			std::string temporary = std::to_string(fractional_part_to_print);
			for (std::size_t printed = 0; printed < temporary.size(); printed++)
			{
				if (printed && printed % 3 == 0)
					result += format.thousand_separator;
				result += temporary[printed];
			}
		}
	}

	return (result);	
}



std::string HumanReadableFormater::exact_form(double value, format_exact_t const & format) const
{
	std::string result;

	const bool is_neg = (value < 0.);
	if (is_neg)
		value *= -1.0;

	__print_sign(result, is_neg, format);

	if (format.print_thousand_separator == false)
		result += __print_exact_and_simple(value, format);
	else
		result += __print_exact_and_complex(value, format);

	return (result);
}




std::string HumanReadableFormater::short_form(double value) const
{
	return (short_form(value, default_format_short));
}

std::string HumanReadableFormater::exact_form(double value) const
{
	return (exact_form(value, default_format_exact));
}

