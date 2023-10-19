#ifndef SFML_HEX_HH
#define SFML_HEX_HH




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

sf::Vector2f to_pixel(Coord const &, ) const;
void to_pixel(Coord const &, std::array<sf::Vector2f, 6> &) const;
void to_pixel(Coord const &, std::vector<sf::Vector2f> &) const;

void append_hex(sf::VertexArray & target,
                Coord const & coord,
                sf::Vector2f const & texture_center,
                std::array<sf::Vector2f, 6> const & texture_corner);

void append_hex(sf::VertexArray & target, Coord const & coord, sf::Color);

void append_hex_vertice(sf::VertexArray & target,
                        Coord const & coord,
                        int corner_start, int corner_end,
                        float thickness,
                        sf::Color color_start, sf::Color color_end);




// With custom layout

sf::Vector2f corner(Layout const &, int corner);
void corner(Layout const &, std::array<sf::Vector2f, 6> &);
void corner(Layout const &, std::vector<sf::Vector2f> &);

void vertice(Layout const &, int dir, sf::Vector2f * result);
void vertice(Layout const &, direction_t dir, sf::Vector2f * result);

sf::Vector2f to_pixel(Layout const &, Coord const &) const;
void to_pixel(Layout const &, Coord const &, std::array<sf::Vector2f, 6> &) const;
void to_pixel(Layout const &, Coord const &, std::vector<sf::Vector2f> &) const;

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
                        int corner_start, int corner_end,
                        float thickness,
                        sf::Color color_start, sf::Color color_end);




} //  hex




#endif // SFML_HEX_HH
