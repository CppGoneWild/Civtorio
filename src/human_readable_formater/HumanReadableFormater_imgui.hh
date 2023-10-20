#ifndef HUMAN_READABLE_FORMATER_IMGUI_HH
#define HUMAN_READABLE_FORMATER_IMGUI_HH


#include "HumanReadableFormater.hh"



namespace ImGui
{


bool Widget(HumanReadableFormater::format_short_t &);
bool Widget(HumanReadableFormater::format_exact_t &);

bool TreeNode(const char* label, HumanReadableFormater::format_short_t &);
bool TreeNode(const char* label, HumanReadableFormater::format_exact_t &);


bool Widget(HumanReadableFormater::format_short_t const &);
bool Widget(HumanReadableFormater::format_exact_t const &);

bool TreeNode(const char* label, HumanReadableFormater::format_short_t const &);
bool TreeNode(const char* label, HumanReadableFormater::format_exact_t const &);



// Widgets: Value() Helpers.
// - Those are merely shortcut to calling Text() with a format string. Output single value in "name: value" format (tip: freely declare more in your code to handle your types. you can add functions to the ImGui namespace)
void ValueShort(const char* prefix, double, HumanReadableFormater::format_short_t const &);
void ValueExact(const char* prefix, double, HumanReadableFormater::format_exact_t const &);

void ValueShort(const char* prefix, double);
void ValueExact(const char* prefix, double);



} // ImGui



#endif // HUMAN_READABLE_FORMATER_IMGUI_HH