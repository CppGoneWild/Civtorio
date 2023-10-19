#ifndef HEX_HH
#define HEX_HH






#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <bitset>




namespace hex {
	class Coord;
	class FractionalCoord;
	class OffestCoord;
	class DoubledCoord;
}




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////                                                                        //// 
//// https://www.redblobgames.com/grids/hexagons/                           ////
////                                                                        ////
//// case                                                                   ////
//// - Pointy Top                                                           ////
//// - Even-R                                                               ////
//// - Rectangular Map storage                                              ////
//// 	- 2D-array                                                            ////
////                                                                        ////
////////////////////////////////////////////////////////////////////////////////
////                                                                        ////
////                             X     X                                    ////
////                            / \   / \                                   ////
////                           /   \ /   \                                  ////
////                          Y     Y     Y                                 ////
////                          |     |     |                                 ////
////                          |     |     |                                 ////
////       1                  X     X     X                       X         ////
////      / \                / \   / \   / \                   1 / \ 0      ////
////     /   \              /   \ /   \ /   \                   /   \       ////
////    2     0            Y     Y     Y     Y                 Y     Y      ////
////    |     |            |     |     |     |                 |     |      ////
////    |     |            |     |     |     |               2 |     | 5    ////
////    3     5            X     X     X     X                 X     X      ////
////     \   /              \   / \   / \   /                   \   /       ////
////      \ /                \ /   \ /   \ /                   3 \ / 4      ////
////       4                  Y     Y     Y                       Y         ////
////                          |     |     |                                 ////
////                          |     |     |                                 ////
////  Corners Idx             X     X     X                 Vertices Idx    ////
////                           \   / \   /                                  ////
////                            \ /   \ /                                   ////
////                             Y     Y                                    ////
////                                                                        ////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////




/*******************************************************************************
                      ___                __  _                 __
                 ____/ (_)_______  _____/ /_(_)___  ____      / /_
                / __  / / ___/ _ \/ ___/ __/ / __ \/ __ \    / __/
               / /_/ / / /  /  __/ /__/ /_/ / /_/ / / / /   / /_
               \__,_/_/_/   \___/\___/\__/_/\____/_/ /_/____\__/
                                                      /_____/
*******************************************************************************/






namespace hex
{



enum class direction_t
{
	East      = 0,
	NorthEast = 1,
	NorthWest = 2,
	West      = 3,
	SouthWest = 4,
	SouthEast = 5,
	__MAX
};

std::string const & encode_direction(hex::direction_t);
std::string encode_direction(std::bitset<6>);

std::bitset<6> decode_direction(std::string const &);


} // hex



std::string const & to_string(hex::direction_t);
std::ostream & operator<<(std::ostream &, hex::direction_t);







/*******************************************************************************
                      __                            __
                     / /   ____ ___  ______  __  __/ /_
                    / /   / __ `/ / / / __ \/ / / / __/
                   / /___/ /_/ / /_/ / /_/ / /_/ / /_
                  /_____/\__,_/\__, /\____/\__,_/\__/
                              /____/
*******************************************************************************/






namespace hex
{







struct Layout
{
	static constexpr int EVEN = 1;
	static constexpr int ODD = -1;

	static constexpr int offset_type = EVEN;

	struct Orientation
	{
		double f0 = 0.;
		double f1 = 0.;
		double f2 = 0.;
		double f3 = 0.;
		double b0 = 0.;
		double b1 = 0.;
		double b2 = 0.;
		double b3 = 0.;
		double start_angle = 0.;
		constexpr Orientation(double f0_, double f1_, double f2_, double f3_, double b0_, double b1_, double b2_, double b3_, double start_angle_)
		: f0(f0_), f1(f1_), f2(f2_), f3(f3_), b0(b0_), b1(b1_), b2(b2_), b3(b3_), start_angle(start_angle_)
		{}
	};
	static const Orientation orientation;


	double size_x;
	double size_y;
	double origin_x;
	double origin_y;
	sf::Vector2f corners[6];

	Layout(double s_x, double s_y, double o_x, double o_y);


	sf::Vector2f __corner(int corner) const;

};

 // it's POINTY_TOP and even-r
extern Layout default_layout;






} // hex






/*******************************************************************************
                         ______                     __
                        / ____/___  ____  _________/ /
                       / /   / __ \/ __ \/ ___/ __  /
                      / /___/ /_/ / /_/ / /  / /_/ /
                      \____/\____/\____/_/   \__,_/
                      
*******************************************************************************/






namespace hex
{








class Coord
{
public:
	Coord()              = default;
	Coord(Coord const &) = default;
	Coord(Coord &&)      = default;
	~Coord()             = default;

	Coord & operator=(Coord const &) = default;
	Coord & operator=(Coord &&)      = default;


	Coord(int, int);
	Coord(int, int, int);
	explicit Coord(FractionalCoord const &);
	explicit Coord(OffestCoord const &);
	explicit Coord(DoubledCoord const &);

	int q() const;
	int r() const;
	int s() const;


	Coord & operator+=(Coord const &);
	Coord & operator-=(Coord const &);
	Coord & operator*=(int);


	Coord & rotate_left();
	Coord & rotate_right();


	Coord rotate_left() const;
	Coord rotate_right() const;


	static Coord neighbor(direction_t);
	static Coord neighbor(int);

	Coord neighbor_of(direction_t) const;
	Coord neighbor_of(int) const;
	void neighbor_of(std::array<Coord, static_cast<std::size_t>(direction_t::__MAX)> &) const;
	void neighbor_of(std::vector<Coord> &) const;


	int distance() const;
	int distance(Coord const &) const;


private:
   int m_q = 0;
   int m_r = 0;
   int m_s = 0;
};



std::vector<Coord> line(Coord const &, Coord const &);
void line(std::vector<Coord> &, Coord const &, Coord const &);


std::vector<Coord> range(Coord const &, int);
void range(std::vector<Coord> &, Coord const &, int);


std::vector<Coord> ring(Coord const &, int);
void ring(std::vector<Coord> &, Coord const &, int);


std::vector<Coord> spiral(Coord const &, int);
void spiral(std::vector<Coord> &, Coord const &, int);





} // hex



bool operator==(hex::Coord const &, hex::Coord const &);
bool operator!=(hex::Coord const &, hex::Coord const &);
bool operator<(hex::Coord const &, hex::Coord const &);


hex::Coord operator+(hex::Coord const &, hex::Coord const &);
hex::Coord operator-(hex::Coord const &, hex::Coord const &);

hex::Coord operator*(hex::Coord const &, int);
hex::Coord operator*(int, hex::Coord const &);


std::string to_string(hex::Coord const &);
std::ostream & operator<<(std::ostream &, hex::Coord const &);






/*******************************************************************************
    ______                __  _                   ________                     __
   / ____/________ ______/ /_(_)___  ____  ____ _/ / ____/___  ____  _________/ /
  / /_  / ___/ __ `/ ___/ __/ / __ \/ __ \/ __ `/ / /   / __ \/ __ \/ ___/ __  /
 / __/ / /  / /_/ / /__/ /_/ / /_/ / / / / /_/ / / /___/ /_/ / /_/ / /  / /_/ /
/_/   /_/   \__,_/\___/\__/_/\____/_/ /_/\__,_/_/\____/\____/\____/_/   \__,_/

*******************************************************************************/






namespace hex
{



class FractionalCoord
{
public:
	FractionalCoord()                        = default;
	FractionalCoord(FractionalCoord const &) = default;
	FractionalCoord(FractionalCoord &&)      = default;
	~FractionalCoord()                       = default;

	FractionalCoord & operator=(FractionalCoord const &) = default;
	FractionalCoord & operator=(FractionalCoord &&)      = default;

	FractionalCoord(double, double, double);
	FractionalCoord(Coord const &);

	FractionalCoord & operator+=(FractionalCoord const &);
	FractionalCoord & operator-=(FractionalCoord const &);
	FractionalCoord & operator*=(double);

	double q() const;
	double r() const;
	double s() const;

	FractionalCoord lerp(FractionalCoord const & oth, double t) const;

private:
   double m_q = 0.;
   double m_r = 0.;
   double m_s = 0.;
};



FractionalCoord lerp(FractionalCoord const & a, FractionalCoord const & b, double t);



} // hex



bool operator==(hex::FractionalCoord const &, hex::FractionalCoord const &);
bool operator!=(hex::FractionalCoord const &, hex::FractionalCoord const &);
bool operator<(hex::FractionalCoord const &, hex::FractionalCoord const &);


hex::FractionalCoord operator+(hex::FractionalCoord const &, hex::FractionalCoord const &);
hex::FractionalCoord operator-(hex::FractionalCoord const &, hex::FractionalCoord const &);

hex::FractionalCoord operator*(hex::FractionalCoord const &, double);
hex::FractionalCoord operator*(double, hex::FractionalCoord const &);


std::string to_string(hex::FractionalCoord const &);
std::ostream & operator<<(std::ostream &, hex::FractionalCoord const &);






/*******************************************************************************
              ____  ________          __  ______                     __
             / __ \/ __/ __/__  _____/ /_/ ____/___  ____  _________/ /
            / / / / /_/ /_/ _ \/ ___/ __/ /   / __ \/ __ \/ ___/ __  /
           / /_/ / __/ __/  __(__  ) /_/ /___/ /_/ / /_/ / /  / /_/ /
           \____/_/ /_/  \___/____/\__/\____/\____/\____/_/   \__,_/
           
*******************************************************************************/






namespace hex
{



class OffestCoord
{
public:
	OffestCoord()                    = default;
	OffestCoord(OffestCoord const &) = default;
	OffestCoord(OffestCoord &&)      = default;
	~OffestCoord()                   = default;

	OffestCoord & operator=(OffestCoord const &) = default;
	OffestCoord & operator=(OffestCoord &&)      = default;

	OffestCoord(int, int);
	explicit OffestCoord(Coord const &);
	explicit OffestCoord(FractionalCoord const &);

	OffestCoord & operator+=(OffestCoord const &);
	OffestCoord & operator-=(OffestCoord const &);

	int col() const;
	int row() const;

private:
	int m_col = 0;
	int m_row = 0;
};



} // hex



bool operator==(hex::OffestCoord const &, hex::OffestCoord const &);
bool operator!=(hex::OffestCoord const &, hex::OffestCoord const &);
bool operator<(hex::OffestCoord const &, hex::OffestCoord const &);


hex::OffestCoord operator+(hex::OffestCoord const &, hex::OffestCoord const &);
hex::OffestCoord operator-(hex::OffestCoord const &, hex::OffestCoord const &);


std::string to_string(hex::DoubledCoord const &);
std::ostream & operator<<(std::ostream &, hex::DoubledCoord const &);






/*******************************************************************************
          ____              __    __         ________                     __
         / __ \____  __  __/ /_  / /__  ____/ / ____/___  ____  _________/ /
        / / / / __ \/ / / / __ \/ / _ \/ __  / /   / __ \/ __ \/ ___/ __  /
       / /_/ / /_/ / /_/ / /_/ / /  __/ /_/ / /___/ /_/ / /_/ / /  / /_/ /
      /_____/\____/\__,_/_.___/_/\___/\__,_/\____/\____/\____/_/   \__,_/
      
*******************************************************************************/






namespace hex
{



class DoubledCoord
{
public:
	DoubledCoord()                     = default;
	DoubledCoord(DoubledCoord const &) = default;
	DoubledCoord(DoubledCoord &&)      = default;
	~DoubledCoord()                    = default;

	DoubledCoord & operator=(DoubledCoord const &) = default;
	DoubledCoord & operator=(DoubledCoord &&)      = default;

	DoubledCoord(int, int);
	explicit DoubledCoord(Coord const &);
	explicit DoubledCoord(FractionalCoord const &);

	DoubledCoord & operator+=(DoubledCoord const &);
	DoubledCoord & operator-=(DoubledCoord const &);

	int col() const;
	int row() const;

private:
	int m_col = 0;
	int m_row = 0;
};



} // hex



bool operator==(hex::DoubledCoord const &, hex::DoubledCoord const &);
bool operator!=(hex::DoubledCoord const &, hex::DoubledCoord const &);
bool operator<(hex::DoubledCoord const &, hex::DoubledCoord const &);


hex::DoubledCoord operator+(hex::DoubledCoord const &, hex::DoubledCoord const &);
hex::DoubledCoord operator-(hex::DoubledCoord const &, hex::DoubledCoord const &);


std::string to_string(hex::DoubledCoord const &);
std::ostream & operator<<(std::ostream &, hex::DoubledCoord const &);





/*******************************************************************************
                    ____            __  __  ___
                   / __ \___  _____/ /_/  |/  /___ _____
                  / /_/ / _ \/ ___/ __/ /|_/ / __ `/ __ \
                 / _, _/  __/ /__/ /_/ /  / / /_/ / /_/ /
                /_/ |_|\___/\___/\__/_/  /_/\__,_/ .___/
                                                /_/
*******************************************************************************/









namespace hex
{




template <class T>
class RectMap
{
public:
	RectMap()                   = default;
	RectMap(RectMap<T> const &) = default;
	RectMap(RectMap<T> &&)      = default;
	~RectMap()                  = default;

	RectMap<T> & operator=(RectMap<T> const &) = default;
	RectMap<T> & operator=(RectMap<T> &&)      = default;


	using line_t = std::vector<T>;
	using root_t = std::vector<line_t>;

	RectMap(std::size_t, std::size_t, T const & def = T());

	void resize(std::size_t, std::size_t, T const & def = T());

	std::size_t height() const;
	std::size_t width() const;

	bool is_in_bound(Coord const &) const;
	bool is_in_bound(OffestCoord const &) const;

	T const & operator[](Coord const &) const;
	T const & operator[](OffestCoord const &) const;

	T & operator[](Coord const &);
	T & operator[](OffestCoord const &);

private:
	root_t m_data;

	Coord m_max_coord;
};





} // hex




template <class T>
hex::RectMap<T>::RectMap(std::size_t height, std::size_t width, T const & def)
: m_data(height, line_t(width, def))
, m_max_coord(OffestCoord(height, width))
{}



template <class T>
void hex::RectMap<T>::resize(std::size_t height, std::size_t width, T const & def)
{
	m_max_coord = Coord(OffestCoord(height, width));

	m_data.resize(height);
	for (auto it = m_data.begin(); it != m_data.end(); ++it)
		it->resize(width, def);
}



template <class T>
std::size_t hex::RectMap<T>::height() const
{
	return (m_max_coord.row());
}

template <class T>
std::size_t hex::RectMap<T>::width() const
{
	return (m_max_coord.col());
}




template <class T>
bool hex::RectMap<T>::is_in_bound(Coord const & c) const
{
	return (is_in_bound(OffestCoord(c)));
}

template <class T>
bool hex::RectMap<T>::is_in_bound(OffestCoord const & c) const
{
	return (c.row() >= 0 && c.col() >= 0 &&
	        c.row() < m_max_coord.row() &&
	        c.col() < m_max_coord.col());
}



template <class T>
T const & hex::RectMap<T>::operator[](Coord const & c) const
{
	return ((*this)[OffestCoord(c)]);
}

template <class T>
T const & hex::RectMap<T>::operator[](OffestCoord const & c) const
{
	return (m_data[c.row()][c.col()]);
}



template <class T>
T & hex::RectMap<T>::operator[](Coord const & c)
{
	return ((*this)[OffestCoord(c)]);
}

template <class T>
T & hex::RectMap<T>::operator[](OffestCoord const & c)
{
	return (m_data[c.row()][c.col()]);
}












/*******************************************************************************
                 _       __
                | |     / /________ _____  ____  ___  _____
                | | /| / / ___/ __ `/ __ \/ __ \/ _ \/ ___/
                | |/ |/ / /  / /_/ / /_/ / /_/ /  __/ /
                |__/|__/_/   \__,_/ .___/ .___/\___/_/
                                 /_/   /_/
*******************************************************************************/





namespace hex
{


class Wrapper
{
public:
	Wrapper()                = default;
	Wrapper(Wrapper const &) = default;
	Wrapper(Wrapper &&)      = default;
	~Wrapper()               = default;

	Wrapper & operator=(Wrapper const &) = default;
	Wrapper & operator=(Wrapper &&)      = default;

	Wrapper(bool wrap_horizontaly, bool wrap_verticaly = false);

	bool wrap_horizontaly() const;
	bool wrap_verticaly() const;

	void set_wrap_horizontaly(bool);
	void set_wrap_verticaly(bool);

	template <class T>
	bool wrap(RectMap<T> const &, OffestCoord &) const;
	template <class T>
	bool wrap(RectMap<T> const &, Coord const &, Coord & result) const;
	template <class T>
	bool wrap(RectMap<T> const &, Coord const &, OffestCoord & result) const;
	template <class T>
	bool wrap(RectMap<T> const &, OffestCoord const &, OffestCoord & result) const;

private:
	bool m_wrap_horizontaly = false;
	bool m_wrap_verticaly = false;
}


} // hex





template <class T>
bool hex::Wrapper::wrap(RectMap<T> const & map, OffestCoord & coord) const
{
	OffestCoord result;

	bool ret = wrap(map, coord, result);
	if (ret)
		coord = result;

	return (ret);
}

template <class T>
bool hex::Wrapper::wrap(RectMap<T> const & map, Coord const & coord, Coord & result) const
{
	OffestCoord tmp;
	bool ret = wrap(map, OffestCoord(coord), tmp);
	result = Coord(tmp);
	return (ret);
}

template <class T>
bool hex::Wrapper::wrap(RectMap<T> const & map, Coord const & coord, OffestCoord & result) const
{
	return (wrap(map, OffsetCoord(coord), result));
}

template <class T>
bool hex::Wrapper::wrap(RectMap<T> const & map, OffestCoord const & coord, OffestCoord & result) const
{
	int wrapped_col = coord.col();
	int wrapped_row = coord.row();

	if (m_wrap_horizontaly)
		wrapped_col %= map.width();
	if (m_wrap_verticaly)
		wrapped_row %= map.height();

	result = OffestCoord(col, row);

	return (map.is_in_bound(coord));
}







#endif // HEX_HH
