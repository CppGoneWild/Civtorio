#ifndef SFML_VECTOR_EXT_HH
#define SFML_VECTOR_EXT_HH



#include "math_ext.hh"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>
#include <cassert>


class VectorArray;


template <class T>
sf::Vector2<T> & operator*=(sf::Vector2<T> & left, sf::Vector2<T> const & right);
template <class T>
sf::Vector2<T> operator*(sf::Vector2<T> const & left, sf::Vector2<T> const & right);



template <class T>
sf::Vector2<T> & operator/=(sf::Vector2<T> & left, sf::Vector2<T> const & right);
template <class T>
sf::Vector2<T> operator/(sf::Vector2<T> const & left, sf::Vector2<T> const & right);



template <class T>
T get_magnitude_sq(sf::Vector2<T> const &);
template <class T>
float get_magnitude(sf::Vector2<T> const &);



inline sf::Vector2f get_unitary_vector(sf::Vector2i const &);
inline sf::Vector2f get_unitary_vector(sf::Vector2u const &);
inline sf::Vector2f get_unitary_vector(sf::Vector2f const &);



template <class T>
T dot_product(sf::Vector2<T> const &, sf::Vector2<T> const &);



template <class T>
float angle_between_degree(sf::Vector2<T> const &, sf::Vector2<T> const &);
template <class T>
float angle_between_radian(sf::Vector2<T> const &, sf::Vector2<T> const &);



template <class T>
float angle_of_degree(sf::Vector2<T> const &);
template <class T>
float angle_of_radian(sf::Vector2<T> const &);



template <class T>
sf::Vector2f naive_lerp(sf::Vector2<T> const &, sf::Vector2<T> const &, float);



// POLAR x=r y=theta
template <class T>
sf::Vector2f cart_to_polar(sf::Vector2<T> const &);
sf::Vector2f polar_to_cart(sf::Vector2f const &);



template <class T>
std::ostream & operator<<(std::ostream & os, sf::Vector2<T> const &);
template <class T>
std::ostream & operator<<(std::ostream & os, sf::Vector3<T> const &);






enum dbg_sfml_opt
{
	No_opt = 0
, Left_tilt
, Right_tilt
};



std::size_t display_vector(sf::VertexArray & res,
                           sf::Vector2f const & pos, sf::Vector2f const & v,
                           sf::Color h_color, sf::Color v_color,
                           dbg_sfml_opt opt = No_opt);



std::size_t display_vector(sf::VertexArray & res,
                           sf::Vector2f const & pos, sf::Vector2f const & v,
                           sf::Color color);



std::size_t display_position(sf::VertexArray & res,
                             sf::Vector2f const & pos,
                             sf::Color color,
                             float size = 2.5);



std::size_t display_grid(sf::VertexArray & res,
                         sf::Vector2f const & origin,
                         sf::Vector2f const & cell_size,
                         sf::Vector2i const & cell_nbr,
                         sf::Color color);





// Will reserve memory, theoricaly faster than sf::VertexArray overload
std::size_t display_vector(VectorArray & res,
                           sf::Vector2f const & pos, sf::Vector2f const & v,
                           sf::Color h_color, sf::Color v_color,
                           dbg_sfml_opt opt = No_opt);



// Will reserve memory, theoricaly faster than sf::VertexArray overload
std::size_t display_vector(VectorArray & res,
                           sf::Vector2f const & pos, sf::Vector2f const & v,
                           sf::Color color);



// Will reserve memory, theoricaly faster than sf::VertexArray overload
std::size_t display_position(VectorArray & res,
                             sf::Vector2f const & pos,
                             sf::Color color,
                             float size = 2.5);



// Will reserve memory, theoricaly faster than sf::VertexArray overload
std::size_t display_grid(VectorArray & res,
                         sf::Vector2f const & origin,
                         sf::Vector2f const & cell_size,
                         sf::Vector2i const & cell_nbr,
                         sf::Color color);





bool imgui_InputVector(char const * name, sf::Vector2i &);
bool imgui_InputVector(char const * name, sf::Vector2u &);
bool imgui_InputVector(char const * name, sf::Vector2f &);

bool imgui_InputVector(char const * name, sf::Vector3<int> &);
bool imgui_InputVector(char const * name, sf::Vector3<unsigned int> &);
bool imgui_InputVector(char const * name, sf::Vector3<float> &);

bool imgui_DragVector(char const * name, sf::Vector2i &, int speed = 1, int min = 0, int max = 0);
bool imgui_DragVector(char const * name, sf::Vector2u &, float speed = 1, unsigned int const * min = nullptr, unsigned int const * max = nullptr);
bool imgui_DragVector(char const * name, sf::Vector2f &, float speed = 1, float min = 0, float max = 0);


void imgui_TextVector(sf::Vector2i const &);
void imgui_TextVector(sf::Vector2u const &);
void imgui_TextVector(sf::Vector2f const &);

void imgui_TextVector(char const * name, sf::Vector2i const &);
void imgui_TextVector(char const * name, sf::Vector2u const &);
void imgui_TextVector(char const * name, sf::Vector2f const &);




#include "sfml_vector_ext.hpp"



#endif // SFML_VECTOR_EXT_HH