#include "hex_imgui.hh"


bool ImGui::DragHex(const char* label, hex::Coord & value, float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
{
	bool ret = false;
	int tmp[3] { value.q(), value.r(), value.s() };

	ImGui::PushID(label);

	ImGui::Text("%s:", label);
	ImGui::SameLine();


	ret |= ImGui::DragInt("q", &tmp[0], v_speed, v_min, v_max, format, flags);
	ImGui::SameLine();

	ret |= ImGui::DragInt("r", &tmp[1], v_speed, v_min, v_max, format, flags);
	ImGui::SameLine();

	ImGui::BeginDisabled(true);
	ImGui::DragInt("s", &tmp[3], v_speed, v_min, v_max, format, flags);
	ImGui::EndDisabled();

	ImGui::PopID();

	if (ret)
		value = hex::Coord(tmp[0], tmp[1]);

	return (ret);
}

bool ImGui::DragHex(const char* label, hex::OffsetCoord & value, float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
{
	bool ret = false;
	int tmp[2] { value.col(), value.row() };

	ImGui::PushID(label);

	ImGui::Text("%s:", label);
	ImGui::SameLine();


	ret |= ImGui::DragInt("col", &tmp[0], v_speed, v_min, v_max, format, flags);
	ImGui::SameLine();

	ret |= ImGui::DragInt("row", &tmp[1], v_speed, v_min, v_max, format, flags);

	ImGui::PopID();

	if (ret)
		value = hex::OffsetCoord(tmp[0], tmp[1]);

	return (ret);
}


//bool ImGui::SliderHex(const char* label, hex::Coord & value, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
//{}

//bool ImGui::SliderHex(const char* label, hex::OffsetCoord & value, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
//{}


//bool ImGui::VSliderHex(const char* label, const ImVec2& size, hex::Coord & value, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
//{}

//bool ImGui::VSliderHex(const char* label, const ImVec2& size, hex::OffsetCoord & value, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
//{}


bool ImGui::InputHex(const char* label, hex::Coord & value, int step, int step_fast, ImGuiInputTextFlags flags)
{
	bool ret = false;
	int tmp[3] { value.q(), value.r(), value.s() };

	ImGui::PushID(label);

	ImGui::Text("%s:", label);
	ImGui::SameLine();


	ret |= ImGui::InputInt("q", &tmp[0], step, step_fast, flags);
	ImGui::SameLine();

	ret |= ImGui::InputInt("r", &tmp[1], step, step_fast, flags);
	ImGui::SameLine();

	ImGui::BeginDisabled(true);
	ImGui::InputInt("s", &tmp[3], step, step_fast, flags);
	ImGui::EndDisabled();

	ImGui::PopID();

	if (ret)
		value = hex::Coord(tmp[0], tmp[1]);

	return (ret);
}

bool ImGui::InputHex(const char* label, hex::OffsetCoord & value, int step, int step_fast, ImGuiInputTextFlags flags)
{
	bool ret = false;
	int tmp[2] { value.col(), value.row() };

	ImGui::PushID(label);

	ImGui::Text("%s:", label);
	ImGui::SameLine();


	ret |= ImGui::InputInt("col", &tmp[0], step, step_fast, flags);
	ImGui::SameLine();

	ret |= ImGui::InputInt("row", &tmp[1], step, step_fast, flags);

	ImGui::PopID();

	if (ret)
		value = hex::OffsetCoord(tmp[0], tmp[1]);

	return (ret);
}


void ImGui::Value(const char* prefix, hex::Coord const & value)
{
	ImGui::Text("%s[%d, %d, %d]", prefix, value.q(), value.r(), value.s());
}

void ImGui::Value(const char* prefix, hex::OffsetCoord const & value)
{
	ImGui::Text("%s[%d, %d]", prefix, value.col(), value.row());
}
