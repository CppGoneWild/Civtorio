#include "HumanReadableFormater_imgui.hh"

#include "imgui.h"




static bool __input_nb_digit(int & nb_digit)
{
	bool ret = false;

	ret |= ImGui::DragInt("Nb Digit Afert Decimal", &nb_digit, 1.0, 0, 18);
	if (nb_digit < 0)
	{
		nb_digit = 0;
		ret = true;
	}

	return (ret);
}


static bool __input_char(const char * label, char & c)
{
	char buf[2] {0};
	bool ret = false;

	buf[0] = c;

	ret |= ImGui::InputText(label, buf, sizeof(buf));
	if (ret)
		c = buf[0];

	if (c == 0)
	{
		c = '*';
		ret = true;
	}

	return (ret);
}

static bool __input_short_type(HumanReadableFormater::format_short_t::type_t & t)
{
	static const char *str[] = { "SI", "MONETARY", "MASS" };
	int current_idx = static_cast<int>(t);
	bool ret = false;

	if (current_idx < 0 || current_idx >= 3)
	{
		current_idx = 0;
		ret = true;
	}

	ret |= ImGui::ListBox("Type", &current_idx, str, 3);

	if (ret)
	{
		if (current_idx < 0 || current_idx >= 3)
			current_idx = 0;
		t = static_cast<HumanReadableFormater::format_short_t::type_t>(current_idx);
	}

	return (ret);
}

static bool __input_common_format(HumanReadableFormater::format_t & format)
{
	bool ret = false;

	__input_nb_digit(format.nb_digit_after_decimal_sep);
	__input_char("Decimal Sep.", format.decimal_separator);

	ret |= ImGui::Checkbox("Always Sign", &format.always_sign_char);

	ImGui::BeginDisabled(format.always_sign_char);
	ret |= ImGui::Checkbox("Trailling Space", &format.trail_space_if_positive);
	ImGui::EndDisabled();

	ImGui::BeginDisabled(format.nb_digit_after_decimal_sep != 0);
	ret |= ImGui::Checkbox("Nb Digit Auto", &format.auto_nb_digit);
	ImGui::EndDisabled();

	return (ret);
}





bool ImGui::Widget(HumanReadableFormater::format_short_t & format)
{
	bool ret = false;

	ret |= __input_common_format(format);


	ret |= ImGui::Checkbox("Long Form", &format.print_long_form);
	ret |= ImGui::Checkbox("Ending Space", &format.space_after_number);

	ret |= __input_short_type(format.type);

	return (ret);
}


bool ImGui::Widget(HumanReadableFormater::format_exact_t & format)
{
	bool ret = false;

	ret |= __input_common_format(format);

	__input_char("Thousand Sep.", format.decimal_separator);
	ret |= ImGui::Checkbox("Print Thousand Sep.", &format.print_thousand_separator);

	return (ret);
}




bool ImGui::TreeNode(const char* label, HumanReadableFormater::format_short_t & format)
{}


bool ImGui::TreeNode(const char* label, HumanReadableFormater::format_exact_t & format)
{}




bool ImGui::Widget(HumanReadableFormater::format_short_t const & format)
{}


bool ImGui::Widget(HumanReadableFormater::format_exact_t const & format)
{}




bool ImGui::TreeNode(const char* label, HumanReadableFormater::format_short_t const & format)
{}


bool ImGui::TreeNode(const char* label, HumanReadableFormater::format_exact_t const & format)
{}






void ImGui::ValueShort(const char* prefix, double value, HumanReadableFormater::format_short_t const & format)
{
	static const HumanReadableFormater formater;
	std::string tmp = formater.short_form(value, format);

	ImGui::Text("%s%s", prefix, tmp.c_str());
}


void ImGui::ValueExact(const char* prefix, double value, HumanReadableFormater::format_exact_t const & format)
{
	static const HumanReadableFormater formater;
	std::string tmp = formater.exact_form(value, format);

	ImGui::Text("%s%s", prefix, tmp.c_str());
}




void ImGui::ValueShort(const char* prefix, double value)
{
	static const HumanReadableFormater::format_short_t format;
	ValueShort(prefix, value, format);
}


void ImGui::ValueExact(const char* prefix, double value)
{
	static const HumanReadableFormater::format_exact_t format;
	ValueExact(prefix, value, format);
}
