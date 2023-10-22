#include "hex_sfml.hh"


#include "sfml_vector_ext.hh"

#include <cmath>
#include <cassert>






static void __append_segment(sf::VertexArray & target,
                             sf::Vector2f const & start, sf::Vector2f const & end,
                             float thickness,
                             sf::Color color_start, sf::Color color_end)
{
	assert(sf::Triangles == target.getPrimitiveType());

	sf::Vector2f u_line = get_unitary_vector(end - start);
	u_line = sf::Vector2f(u_line.y, u_line.x);

	target.append(sf::Vertex(start + ( u_line * thickness), color_start));
	target.append(sf::Vertex(start + (-u_line * thickness), color_start));
	target.append(sf::Vertex(end   + (-u_line * thickness), color_end));

	target.append(sf::Vertex(end   + (-u_line * thickness), color_end));
	target.append(sf::Vertex(end   + ( u_line * thickness), color_end));
	target.append(sf::Vertex(start + ( u_line * thickness), color_start));
}










sf::Vector2f hex::corner(int c)
{
	return (corner(default_layout, c));
}

void hex::corner(std::array<sf::Vector2f, 6> & result)
{
	return (corner(default_layout, result));
}

void hex::corner(std::vector<sf::Vector2f> & result)
{
	return (corner(default_layout, result));
}




void hex::vertice(int dir, sf::Vector2f * result)
{
	vertice(default_layout, dir, result);
}

void hex::vertice(direction_t dir, sf::Vector2f * result)
{
	vertice(default_layout, static_cast<int>(dir), result);
}




sf::Vector2f hex::to_pixel(Coord const & coord)
{
	return (to_pixel(default_layout, coord));
}

void hex::to_pixel(Coord const & coord,
                   std::array<sf::Vector2f, 6> & result)
{
	to_pixel(default_layout, coord, result);
}

void hex::to_pixel(Coord const & coord,
                   std::vector<sf::Vector2f> & result)
{
	to_pixel(default_layout, coord, result);
}





void hex::from_pixel(sf::Vector2f const & p, Coord & result)
{
	from_pixel(default_layout, p, result);
}

void hex::from_pixel(sf::Vector2f const & p, FractionalCoord & result)
{
	from_pixel(default_layout, p, result);
}




void hex::append_hex(sf::VertexArray & target,
                     Coord const & coord,
                     sf::Vector2f const & texture_center,
                     std::array<sf::Vector2f, 6> const & texture_corner)
{
	append_hex(target, default_layout, coord, texture_center, texture_corner);
}


void hex::append_hex(sf::VertexArray & target, Coord const & coord, sf::Color color)
{
	append_hex(target, default_layout, coord, color);
}


void hex::append_hex_vertice(sf::VertexArray & target,
                             Coord const & coord,
                             int dir,
                             float thickness,
                             sf::Color color_start, sf::Color color_end)
{
	append_hex_vertice(target, default_layout, coord,
	                   static_cast<int>(dir),
	                   thickness, color_start, color_end);
}

void hex::append_hex_vertice(sf::VertexArray & target,
                             Coord const & coord,
                             direction_t dir,
                             float thickness,
                             sf::Color color_start, sf::Color color_end)
{
	append_hex_vertice(target, default_layout, coord,
	                   static_cast<int>(dir),
	                   thickness, color_start, color_end);
}


void hex::append_hex_vertice(sf::VertexArray & target,
                             Coord const & coord,
                             float thickness,
                             sf::Color color)
{
	append_hex_vertice(target, default_layout, coord, thickness, color);
}












sf::Vector2f hex::corner(Layout const & layout, int c)
{
	assert(c >=0 && c < 6);

	return (layout.corners[c]);
}

void hex::corner(Layout const & layout, std::array<sf::Vector2f, 6> & result)
{
	for (int i = 0; i < 6; ++i)
		result[i] = corner(layout, i);
}

void hex::corner(Layout const & layout, std::vector<sf::Vector2f> & result)
{
	for (int i = 0; i < 6; ++i)
		result.emplace_back(corner(layout, i));
}




void hex::vertice(Layout const & layout, int dir, sf::Vector2f * result)
{
	assert(dir >=0 && dir < 6);

	if (dir == 0) // East
	{
		result[0] = layout.corners[5];
		result[1] = layout.corners[0];
	}
	else
	{
		result[0] = layout.corners[dir - 1];
		result[1] = layout.corners[dir];
	}
}

void hex::vertice(Layout const & layout, direction_t dir, sf::Vector2f * result)
{
	vertice(layout, static_cast<int>(dir), result);
}




sf::Vector2f hex::to_pixel(Layout const & layout, Coord const & coord)
{
  double x = (layout.orientation.f0 * coord.q() + layout.orientation.f1 * coord.r()) * layout.size_x;
  double y = (layout.orientation.f2 * coord.q() + layout.orientation.f3 * coord.r()) * layout.size_y;

	return (sf::Vector2f(x + layout.origin_x, y + layout.origin_y));
}

void hex::to_pixel(Layout const & layout, Coord const & coord,
                   std::array<sf::Vector2f, 6> & result)
{
	sf::Vector2f center = to_pixel(layout, coord);
	for (int i = 0; i < 6; ++i)
		result[i] = corner(layout, i) + center;
}

void hex::to_pixel(Layout const & layout, Coord const & coord,
                   std::vector<sf::Vector2f> & result)
{
	sf::Vector2f center = to_pixel(layout, coord);
	for (int i = 0; i < 6; ++i)
		result.emplace_back(corner(layout, i) + center);
}





void hex::from_pixel(Layout const & layout,
                     sf::Vector2f const & pixel,
                     Coord & result)
{
	FractionalCoord tmp;
	from_pixel(layout, pixel, tmp);
	result = Coord(tmp);
}

void hex::from_pixel(Layout const & layout,
                     sf::Vector2f const & p,
                     FractionalCoord & result)
{
	double x = (p.x - layout.origin_x) / layout.size_x;
	double y = (p.y - layout.origin_y) / layout.size_y;

	double q = layout.orientation.b0 * x + layout.orientation.b1 * y;
	double r = layout.orientation.b2 * x + layout.orientation.b3 * y;
	double s = -q -r;

	assert(std::round(q + r + s) == 0);

	result = FractionalCoord(q, r, s);
}





void hex::append_hex(sf::VertexArray & target,
                     Layout const & layout,
                     Coord const & coord,
                     sf::Vector2f const & /*texture_center*/,
                     std::array<sf::Vector2f, 6> const & texture_corner)
{
	assert(sf::Triangles == target.getPrimitiveType());

	sf::Vector2f hex_center = to_pixel(layout, coord);

	target.append(sf::Vertex(hex_center + corner(layout, 1), texture_corner[1]));
	target.append(sf::Vertex(hex_center + corner(layout, 2), texture_corner[2]));
	target.append(sf::Vertex(hex_center + corner(layout, 3), texture_corner[3]));

	target.append(sf::Vertex(hex_center + corner(layout, 1), texture_corner[1]));
	target.append(sf::Vertex(hex_center + corner(layout, 3), texture_corner[3]));
	target.append(sf::Vertex(hex_center + corner(layout, 4), texture_corner[4]));

	target.append(sf::Vertex(hex_center + corner(layout, 1), texture_corner[1]));
	target.append(sf::Vertex(hex_center + corner(layout, 4), texture_corner[4]));
	target.append(sf::Vertex(hex_center + corner(layout, 0), texture_corner[0]));

	target.append(sf::Vertex(hex_center + corner(layout, 0), texture_corner[0]));
	target.append(sf::Vertex(hex_center + corner(layout, 4), texture_corner[4]));
	target.append(sf::Vertex(hex_center + corner(layout, 5), texture_corner[5]));
}

void hex::append_hex(sf::VertexArray & target,
                     Layout const & layout,
                     Coord const & coord,
                     sf::Color color)
{
	assert(sf::Triangles == target.getPrimitiveType());

	sf::Vector2f hex_center = to_pixel(layout, coord);


	target.append(sf::Vertex(hex_center + corner(layout, 1), color));
	target.append(sf::Vertex(hex_center + corner(layout, 2), color));
	target.append(sf::Vertex(hex_center + corner(layout, 3), color));

	target.append(sf::Vertex(hex_center + corner(layout, 1), color));
	target.append(sf::Vertex(hex_center + corner(layout, 3), color));
	target.append(sf::Vertex(hex_center + corner(layout, 4), color));

	target.append(sf::Vertex(hex_center + corner(layout, 1), color));
	target.append(sf::Vertex(hex_center + corner(layout, 4), color));
	target.append(sf::Vertex(hex_center + corner(layout, 0), color));

	target.append(sf::Vertex(hex_center + corner(layout, 0), color));
	target.append(sf::Vertex(hex_center + corner(layout, 4), color));
	target.append(sf::Vertex(hex_center + corner(layout, 5), color));
}




void hex::append_hex_vertice(sf::VertexArray & target,
                             Layout const & layout,
                             Coord const & coord,
                             int dir,
                             float thickness,
                             sf::Color color_start, sf::Color color_end)
{
	sf::Vector2f center = to_pixel(coord);
	sf::Vector2f tmp[2];

	vertice(layout, dir, tmp);

	tmp[0] += center;
	tmp[1] += center;

	__append_segment(target, tmp[0], tmp[1], thickness, color_start, color_end);
}

void hex::append_hex_vertice(sf::VertexArray & target,
                             Layout const & layout,
                             Coord const & coord,
                             direction_t dir,
                             float thickness,
                             sf::Color color_start, sf::Color color_end)
{
	append_hex_vertice(target, layout, coord,
	                   static_cast<int>(dir),
	                   thickness, color_start, color_end);
}


void hex::append_hex_vertice(sf::VertexArray & target,
                             Layout const & layout,
                             Coord const & coord,
                             float thickness,
                             sf::Color color)
{
	for (int i = 0; i < 6; ++i)
		append_hex_vertice(target, layout, coord, i, thickness, color, color);
}