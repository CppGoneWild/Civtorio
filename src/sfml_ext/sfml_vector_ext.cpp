#include "sfml_vector_ext.hh"

#include "imgui.h"






sf::Vector2f polar_to_cart(sf::Vector2f const & v)
{
	sf::Vector2f res;

	res.x = v.x * std::cos(v.y);
	res.y = v.x * std::sin(v.y);

	return (res);
}






std::size_t display_vector(sf::VertexArray & res,
                           sf::Vector2f const & pos, sf::Vector2f const & v,
                           sf::Color h_color, sf::Color v_color,
                           dbg_smfl_opt opt)
{
	assert(sf::Lines == res.getPrimitiveType());


	sf::Vertex h_origin(pos, h_color);
	sf::Vertex h_end(sf::Vector2f(pos.x + v.x, pos.y), h_color);

	res.append(h_origin);
	res.append(h_end);

	sf::Vertex v_origin(pos, v_color);
	sf::Vertex v_end(sf::Vector2f(pos.x, pos.y + v.y), v_color);

	res.append(v_origin);
	res.append(v_end);


	if (opt == Left_tilt || opt == Right_tilt)
	{
			sf::Vertex th_origin(h_end);
			sf::Vertex th_end(sf::Vector2f(th_origin.position.x, th_origin.position.y + (opt == Left_tilt ? 3 : -3)), h_color);

			res.append(th_origin);
			res.append(th_end);

			sf::Vertex tv_origin(v_end);
			sf::Vertex tv_end(sf::Vector2f(tv_origin.position.x + (opt == Left_tilt ? 3 : -3), tv_origin.position.y), v_color);

			res.append(tv_origin);
			res.append(tv_end);

		return (8);
	}

	return (4);
}






std::size_t display_vector(sf::VertexArray & res,
                           sf::Vector2f const & pos, sf::Vector2f const & v,
                           sf::Color color)
{
	assert(sf::Lines == res.getPrimitiveType());

	res.append(sf::Vertex(pos, color));
	res.append(sf::Vertex(pos + v, color));

	return (2);
}






std::size_t display_position(sf::VertexArray & res,
                             sf::Vector2f const & pos,
                             sf::Color color,
                             float size)
{
	assert(sf::Lines == res.getPrimitiveType());

	//AB
	res.append(sf::Vertex(pos + sf::Vector2f(-size,  size), color));
	res.append(sf::Vertex(pos + sf::Vector2f( size,  size), color));

	//BC
	res.append(sf::Vertex(pos + sf::Vector2f( size,  size), color));
	res.append(sf::Vertex(pos + sf::Vector2f( size, -size), color));

	//CD
	res.append(sf::Vertex(pos + sf::Vector2f( size, -size), color));
	res.append(sf::Vertex(pos + sf::Vector2f(-size, -size), color));

	//DA
	res.append(sf::Vertex(pos + sf::Vector2f(-size, -size), color));
	res.append(sf::Vertex(pos + sf::Vector2f(-size,  size), color));

	return (8);
}










std::size_t display_grid_one_cell(sf::VertexArray & res,
                                  sf::Vector2f const & origin,
                                  sf::Vector2f const & cell_size,
                                  sf::Color color)
{
	assert(sf::Lines == res.getPrimitiveType());


	//AB
	res.append(sf::Vertex(origin, color));
	res.append(sf::Vertex(origin + sf::Vector2f(cell_size.x, 0), color));

	//BC
	res.append(sf::Vertex(origin + sf::Vector2f(cell_size.x, 0), color));
	res.append(sf::Vertex(origin + cell_size, color));

	//CD
	res.append(sf::Vertex(origin + cell_size, color));
	res.append(sf::Vertex(origin + sf::Vector2f(0, cell_size.y), color));

	//DA
	res.append(sf::Vertex(origin + sf::Vector2f(0, cell_size.y), color));
	res.append(sf::Vertex(origin, color));

	return (8);
}

std::size_t display_grid(sf::VertexArray & res,
                         sf::Vector2f const & origin,
                         sf::Vector2f const & cell_size,
                         sf::Vector2i const & cell_nbr,
                         sf::Color color)
{
	assert(sf::Lines == res.getPrimitiveType());
	assert(cell_nbr.x >= 0);
	assert(cell_nbr.y >= 0);

	std::size_t nb_vertex_added = 0;

	for (int i = 0; i < cell_nbr.x; ++i)
	{
		for (int ii = 0; ii < cell_nbr.y; ++ii)
		{
			sf::Vector2f tmp = origin;
			tmp.x += cell_size.x * static_cast<float>(i);
			tmp.y += cell_size.y * static_cast<float>(ii);
			nb_vertex_added += display_grid_one_cell(res, tmp, cell_size, color);
		}
	}

	return (nb_vertex_added);
}












bool imgui_InputVector(char const * name, sf::Vector2i &v)
{
	bool res = false;

	ImGui::PushID(name);

	res |= ImGui::InputInt("x", &v.x);
	ImGui::SameLine();
	res |= ImGui::InputInt("y", &v.y);
	ImGui::SameLine();
	ImGui::Text("%s", name);

	ImGui::PopID();

	return (res);
}

bool imgui_InputVector(char const * name, sf::Vector2u &v)
{
	bool res = false;

	ImGui::PushID(name);

	res |= ImGui::InputScalar("x", ImGuiDataType_U32, &v.x);
	ImGui::SameLine();
	res |= ImGui::InputScalar("y", ImGuiDataType_U32, &v.y);
	ImGui::SameLine();
	ImGui::Text("%s", name);

	ImGui::PopID();

	return (res);
}

bool imgui_InputVector(char const * name, sf::Vector2f &v)
{
	bool res = false;

	ImGui::PushID(name);

	res |= ImGui::InputFloat("x", &v.x);
	ImGui::SameLine();
	res |= ImGui::InputFloat("y", &v.y);
	ImGui::SameLine();
	ImGui::Text("%s", name);

	ImGui::PopID();

	return (res);
}






bool imgui_InputVector(char const * name, sf::Vector3<int> &v)
{
	bool res = false;

	ImGui::PushID(name);

	res |= ImGui::InputInt("x", &v.x);
	ImGui::SameLine();
	res |= ImGui::InputInt("y", &v.y);
	ImGui::SameLine();
	res |= ImGui::InputInt("z", &v.z);
	ImGui::SameLine();
	ImGui::Text("%s", name);

	ImGui::PopID();

	return (res);
}

bool imgui_InputVector(char const * name, sf::Vector3<unsigned int> &v)
{
	bool res = false;

	ImGui::PushID(name);

	res |= ImGui::InputScalar("x", ImGuiDataType_U32, &v.x);
	ImGui::SameLine();
	res |= ImGui::InputScalar("y", ImGuiDataType_U32, &v.y);
	ImGui::SameLine();
	res |= ImGui::InputScalar("z", ImGuiDataType_U32, &v.z);
	ImGui::SameLine();
	ImGui::Text("%s", name);

	ImGui::PopID();

	return (res);
}

bool imgui_InputVector(char const * name, sf::Vector3<float> &v)
{
	bool res = false;

	ImGui::PushID(name);

	res |= ImGui::InputFloat("x", &v.x);
	ImGui::SameLine();
	res |= ImGui::InputFloat("y", &v.y);
	ImGui::SameLine();
	res |= ImGui::InputFloat("z", &v.z);
	ImGui::SameLine();
	ImGui::Text("%s", name);

	ImGui::PopID();

	return (res);
}






bool imgui_DragVector(char const * name, sf::Vector2i & v, int speed, int min, int max)
{
	bool res = false;

	ImGui::PushID(name);

	res |= ImGui::DragInt("x", &v.x, speed, min, max);
	ImGui::SameLine();
	res |= ImGui::DragInt("y", &v.y, speed, min, max);
	ImGui::SameLine();
	ImGui::Text("%s", name);

	ImGui::PopID();

	return (res);
}

bool imgui_DragVector(char const * name, sf::Vector2u & v, float speed, unsigned int const * min, unsigned int const * max)
{
	bool res = false;

	ImGui::PushID(name);

	res |= ImGui::DragScalar("x", ImGuiDataType_U32, &v.x, speed, min, max);
	ImGui::SameLine();
	res |= ImGui::DragScalar("y", ImGuiDataType_U32, &v.y, speed, min, max);
	ImGui::SameLine();
	ImGui::Text("%s", name);

	ImGui::PopID();

	return (res);
}

bool imgui_DragVector(char const * name, sf::Vector2f & v, float speed, float min, float max)
{
	bool res = false;

	ImGui::PushID(name);

	res |= ImGui::DragFloat("x", &v.x, speed, min, max);
	ImGui::SameLine();
	res |= ImGui::DragFloat("y", &v.y, speed, min, max);
	ImGui::SameLine();
	ImGui::Text("%s", name);

	ImGui::PopID();

	return (res);
}






void imgui_TextVector(sf::Vector2i const & v)
{
	ImGui::Text("[%i, %i]", v.x, v.y);
}

void imgui_TextVector(sf::Vector2u const & v)
{
	ImGui::Text("[%u, %u]", v.x, v.y);
}

void imgui_TextVector(sf::Vector2f const & v)
{
	ImGui::Text("[%f, %f]", v.x, v.y);
}





void imgui_TextVector(char const * name, sf::Vector2i const & v)
{
	ImGui::Text("%s [%i, %i]", name, v.x, v.y);
}

void imgui_TextVector(char const * name, sf::Vector2u const & v)
{
	ImGui::Text("%s [%u, %u]", name, v.x, v.y);
}

void imgui_TextVector(char const * name, sf::Vector2f const & v)
{
	ImGui::Text("%s [%f, %f]", name, v.x, v.y);
}
