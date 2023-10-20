#ifndef HUMAN_READABLE_FORMATER_HH
#define HUMAN_READABLE_FORMATER_HH


#include <string>


struct HumanReadableFormater
{
	struct format_t
	{
		int  nb_digit_after_decimal_sep = 0;
		char decimal_separator = '.';
		bool always_sign_char = false;
		bool trail_space_if_positive = false; // ignored if always_sign_char is true
		bool auto_nb_digit = true;  // ignored if nb_digit_after_decimal_sep is not 0
	};

	struct format_short_t : public format_t
	{
		enum type_t
		{
			SI,
			MONETARY,
			MASS
		};

		bool print_long_form = false; // short form is 'k', long form is 'kilo'.
		bool space_after_number = true;
		type_t type = MONETARY;
	};

	struct format_exact_t : public format_t
	{
		char thousand_separator = '\'';
		bool print_thousand_separator = true;
	};


	format_short_t default_format_short;
	format_exact_t default_format_exact;


	std::string short_form(double value, format_short_t const &) const;
	std::string exact_form(double value, format_exact_t const &) const;

	std::string short_form(double value) const;
	std::string exact_form(double value) const;
};


#endif // HUMAN_READABLE_FORMATER_HH