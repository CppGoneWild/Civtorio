#ifndef HEX_IMGUI_HH
#define HEX_IMGUI_HH




#include "hex.hh"

#include "imgui.h"




namespace ImGui
{




bool DragHex(const char* label, hex::Coord &, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);
bool DragHex(const char* label, hex::OffsetCoord &, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0);

bool SliderHex(const char* label, hex::Coord &, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
bool SliderHex(const char* label, hex::OffsetCoord &, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);

bool VSliderHex(const char* label, const ImVec2& size, hex::Coord &, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);
bool VSliderHex(const char* label, const ImVec2& size, hex::OffsetCoord &, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0);

bool InputHex(const char* label, hex::OffsetCoord &, int step = 1, int step_fast = 100, ImGuiInputTextFlags flags = 0);
bool InputHex(const char* label, hex::Coord &, int step = 1, int step_fast = 100, ImGuiInputTextFlags flags = 0);

// Widgets: Value() Helpers.
// - Those are merely shortcut to calling Text() with a format string. Output single value in "name: value" format (tip: freely declare more in your code to handle your types. you can add functions to the ImGui namespace)
void Value(const char* prefix, hex::Coord const &);
void Value(const char* prefix, hex::OffsetCoord const &);




} //  ImGui




#endif // HEX_IMGUI_HH
