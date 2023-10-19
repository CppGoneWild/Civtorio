#include "hex_imgui.hh"


bool ImGui::DragHex(const char* label, hex::Coord & value, float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
{}

bool ImGui::DragHex(const char* label, hex::OffestCoord & value, float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
{}


bool ImGui::SliderHex(const char* label, hex::Coord & value, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
{}

bool ImGui::SliderHex(const char* label, hex::OffestCoord & value, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
{}


bool ImGui::VSliderHex(const char* label, const ImVec2& size, hex::Coord & value, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
{}

bool ImGui::VSliderHex(const char* label, const ImVec2& size, hex::OffestCoord & value, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
{}


bool ImGui::InputHex(const char* label, hex::OffestCoord & value, int step, int step_fast, ImGuiInputTextFlags flags)
{}

bool ImGui::InputHex(const char* label, hex::Coord & value, int step, int step_fast, ImGuiInputTextFlags flags)
{}


void ImGui::Value(const char* prefix, hex::Coord const & value)
{}

void ImGui::Value(const char* prefix, hex::OffestCoord const & value)
{}
