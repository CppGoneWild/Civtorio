#ifndef HEX_SFML_HH
#define HEX_SFML_HH




#include <vector>
#include <array>


#include <SFML/Graphics.hpp>


#include "hex.hh"




namespace hex
{




// With default_layout

sf::Vector2f corner(int corner);
void corner(std::array<sf::Vector2f, 6> &);
void corner(std::vector<sf::Vector2f> &);

void vertice(int dir, sf::Vector2f * result);
void vertice(direction_t dir, sf::Vector2f * result);

sf::Vector2f to_pixel(Coord const &);
void to_pixel(Coord const &, std::array<sf::Vector2f, 6> &);
void to_pixel(Coord const &, std::vector<sf::Vector2f> &);

void from_pixel(sf::Vector2f const &, Coord & result);
void from_pixel(sf::Vector2f const &, FractionalCoord & result);

void append_hex(sf::VertexArray & target,
                Coord const & coord,
                sf::Vector2f const & texture_center,
                std::array<sf::Vector2f, 6> const & texture_corner);
void append_hex(sf::VertexArray & target, Coord const & coord, sf::Color);

void append_hex_vertice(sf::VertexArray & target,
                        Coord const & coord,
                        int dir,
                        float thickness,
                        sf::Color color_start, sf::Color color_end);
void append_hex_vertice(sf::VertexArray & target,
                        Coord const & coord,
                        direction_t dir,
                        float thickness,
                        sf::Color color_start, sf::Color color_end);

void append_hex_vertice(sf::VertexArray & target,
                        Coord const & coord,
                        float thickness,
                        sf::Color color);




// With custom layout

sf::Vector2f corner(Layout const &, int corner);
void corner(Layout const &, std::array<sf::Vector2f, 6> &);
void corner(Layout const &, std::vector<sf::Vector2f> &);

void vertice(Layout const &, int dir, sf::Vector2f * result);
void vertice(Layout const &, direction_t dir, sf::Vector2f * result);

sf::Vector2f to_pixel(Layout const &, Coord const &);
void to_pixel(Layout const &, Coord const &, std::array<sf::Vector2f, 6> &);
void to_pixel(Layout const &, Coord const &, std::vector<sf::Vector2f> &);

void from_pixel(Layout const &, sf::Vector2f const &, Coord & result);
void from_pixel(Layout const &, sf::Vector2f const &, FractionalCoord & result);

void append_hex(sf::VertexArray & target,
                Layout const & layout,
                Coord const & coord,
                sf::Vector2f const & texture_center,
                std::array<sf::Vector2f, 6> const & texture_corner);

void append_hex(sf::VertexArray & target,
                Layout const & layout,
                Coord const & coord,
                sf::Color);

void append_hex_vertice(sf::VertexArray & target,
                        Layout const & layout,
                        Coord const & coord,
                        int dir,
                        float thickness,
                        sf::Color color_start, sf::Color color_end);
void append_hex_vertice(sf::VertexArray & target,
                        Layout const & layout,
                        Coord const & coord,
                        direction_t dir,
                        float thickness,
                        sf::Color color_start, sf::Color color_end);

void append_hex_vertice(sf::VertexArray & target,
                        Layout const & layout,
                        Coord const & coord,
                        float thickness,
                        sf::Color color);




} //  hex




#endif // HEX_SFML_HH
