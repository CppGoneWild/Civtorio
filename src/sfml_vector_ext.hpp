






template <class T>
sf::Vector2<T> & operator*=(sf::Vector2<T> & left, sf::Vector2<T> const & right)
{
	left.x *= right.x;
	left.y *= right.y;
	return (left);
}



template <class T>
sf::Vector2<T> operator*(sf::Vector2<T> const & left, sf::Vector2<T> const & right)
{
	sf::Vector2<T> res;(left);
	res *= right;
	return (res);
}






template <class T>
sf::Vector2<T> & operator/=(sf::Vector2<T> & left, sf::Vector2<T> const & right)
{
	left.x /= right.x;
	left.y /= right.y;
	return (left);
}



template <class T>
sf::Vector2<T> operator/(sf::Vector2<T> const & left, sf::Vector2<T> const & right)
{
	sf::Vector2<T> res;(left);
	res /= right;
	return (res);
}






template <class T>
T get_magnitude_sq(sf::Vector2<T> const & v)
{
	return (v.x * v.x + v.y * v.y);
}



template <class T>
float get_magnitude(sf::Vector2<T> const & v)
{
	T tmp = get_magnitude_sq(v);
	return (std::sqrt(static_cast<float>(tmp)));
}






sf::Vector2f get_unitary_vector(sf::Vector2i const & v)
{
	float norm = get_magnitude(v);
	sf::Vector2f tmp(static_cast<float>(v.x), static_cast<float>(v.y));
	tmp /= norm;
	return (tmp);
}



sf::Vector2f get_unitary_vector(sf::Vector2u const & v)
{
	float norm = get_magnitude(v);
	sf::Vector2f tmp(static_cast<float>(v.x), static_cast<float>(v.y));
	tmp /= norm;
	return (tmp);
}



sf::Vector2f get_unitary_vector(sf::Vector2f const & v)
{
	return (v / get_magnitude(v));
}






template <class T>
T dot_product(sf::Vector2<T> const & a, sf::Vector2<T> const & b)
{
	return (a.x * b.x + a.y *b.y);
}






template <class T>
float angle_between_degree(sf::Vector2<T> const & a, sf::Vector2<T> const & b)
{
	float rad = angle_between_radian(a, b);
	return (rad * (180.f/M_PI));
}



template <class T>
float angle_between_radian(sf::Vector2<T> const & a, sf::Vector2<T> const & b)
{
	float dotp = static_cast<float>(dot_product(a, b));

	assert(std::abs(dotp) < 1.f);

	return (std::acos(dotp));
}





template <class T>
float angle_of_degree(sf::Vector2<T> const & v)
{
	rad_to_deg(angle_of_radian(v));
}

template <class T>
float angle_of_radian(sf::Vector2<T> const & v)
{
	sf::Vector2f polar_v = cart_to_polar(v);
	return (round_rad(polar_v.y));
}





template <class T>
sf::Vector2f naive_lerp(sf::Vector2<T> const & a, sf::Vector2<T> const & b, float c)
{
	sf::Vector2f res;

	res.x = naive_lerp(a.x, b.x, c);
	res.y = naive_lerp(a.y, b.y, c);

	return (res);
}






template <class T>
sf::Vector2f cart_to_polar(sf::Vector2<T> const & v)
{
	sf::Vector2f res;

	res.x = std::hypot(v.x, v.y);	
	res.y = std::atan2(v.y, v.x);

	return (res);
}







template <class T>
std::ostream & operator<<(std::ostream & os, sf::Vector2<T> const & v)
{
	os << '[' << v.x << ", " << v.y << ']';
	return (os);
}



template <class T>
std::ostream & operator<<(std::ostream & os, sf::Vector3<T> const & v)
{
	os << '[' << v.x << ", " << v.y  << ", " << v.z << ']';
	return (os);
}
