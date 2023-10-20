#include "hex.hh"


#include <algorithm>
#include <cassert>
#include <cmath>


#define SQRT_OF_3 (1.73205080757)


#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif




static const std::array<hex::Coord, 6> coord_directions = {hex::Coord( 1,  0, -1),  // East
                                                           hex::Coord( 1, -1,  0),  // NorthEast
                                                           hex::Coord( 0, -1,  1),  // NorthWest
                                                           hex::Coord(-1,  0,  1),  // West
                                                           hex::Coord(-1,  1,  0),  // SouthWest
                                                           hex::Coord( 0,  1, -1)}; // SouthEast

static const std::array<hex::Coord, 6> coord_diagonals = {hex::Coord( 2, -1, -1),  // East - NorthEast
                                                          hex::Coord( 1, -2,  1),  // North
                                                          hex::Coord(-1, -1,  2),  // West - NorthWest
                                                          hex::Coord(-2,  1,  1),  // West - SouthWest
                                                          hex::Coord(-1,  2, -1),  // South
                                                          hex::Coord( 1,  1, -2)}; // Est - SouthEast




namespace hex
{


const Layout::Orientation Layout::orientation = Layout::Orientation(SQRT_OF_3,
                                                                    SQRT_OF_3 / 2.0,
                                                                    0.0,
                                                                    3.0 / 2.0,
                                                                    SQRT_OF_3 / 3.0,
                                                                    -1.0 / 3.0,
                                                                    0.0,
                                                                    2.0 / 3.0,
                                                                    0.5);


Layout::Layout(double radius)
: Layout(radius / SQRT_OF_3, radius / 2.0, 0, 0)
{}

Layout::Layout(double s_x, double s_y, double o_x, double o_y)
: size_x(s_x)
, size_y(s_y)
, origin_x(o_x)
, origin_y(o_y)
{
	for (int i = 0; i < 6; ++i)
		corners[i] = __corner(i);
}


sf::Vector2f Layout::__corner(int corner) const
{
  double angle = 2.0 * M_PI * (orientation.start_angle - corner) / 6.0;
	return (sf::Vector2f(size_x * cos(angle), size_y * sin(angle)));
}

Layout default_layout(100.);


} // hex




/*******************************************************************************
                      ___                __  _                 __
                 ____/ (_)_______  _____/ /_(_)___  ____      / /_
                / __  / / ___/ _ \/ ___/ __/ / __ \/ __ \    / __/
               / /_/ / / /  /  __/ /__/ /_/ / /_/ / / / /   / /_
               \__,_/_/_/   \___/\___/\__/_/\____/_/ /_/____\__/
                                                      /_____/
*******************************************************************************/






std::string const & hex::encode_direction(hex::direction_t d)
{
	static const std::array<std::string, 7> ref
	{
		"e",
		"ne",
		"nw",
		"w",
		"se",
		"sw",
		""
	};

	std::size_t idx = std::min(static_cast<std::size_t>(d),
	                           static_cast<std::size_t>(hex::direction_t::__MAX));
	return (ref[idx]);
}

std::string hex::encode_direction(std::bitset<6> dirs)
{
	std::string res;

	if (dirs.count() == 0)
		return (res);

	for (std::size_t i = 0; i < 6; ++i)
		if (dirs.test(i))
			res += encode_direction(static_cast<hex::direction_t>(i));
	return (res);
}


std::bitset<6> hex::decode_direction(std::string const & str)
{
	std::bitset<6> dirs;

	for (std::size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] == 'n')
		{
			++i;
			if (str[i] == 'e')
				dirs.set((std::size_t)(direction_t::NorthEast), true);
			else if (str[i] == 'w')			
				dirs.set((std::size_t)(direction_t::NorthWest), true);
			else
			{
				return (std::bitset<6>());
			}
		}
		else if (str[i] == 's')
		{
			++i;
			if (str[i] == 'e')
				dirs.set((std::size_t)(direction_t::SouthEast), true);
			else if (str[i] == 'w')			
				dirs.set((std::size_t)(direction_t::SouthWest), true);
			else
			{
				return (std::bitset<6>());
			}
		}
		else if (str[i] == 'e')
			dirs.set((std::size_t)(direction_t::East), true);
		else if (str[i] == 'w')			
			dirs.set((std::size_t)(direction_t::West), true);
		else
		{
			return (std::bitset<6>());
		}
	}

	return (dirs);
}




std::string const & to_string(hex::direction_t d)
{
	static constexpr std::size_t __max = static_cast<std::size_t>(hex::direction_t::__MAX);
	static const std::array<std::string, __max + 1> tmp =
	{ "East",
	  "NorthEast",
	  "NorthWest",
	  "West",
	  "SouthWest",
	  "SouthEast",
	  "Unknown"
	};

	std::size_t idx = std::min(static_cast<std::size_t>(d), __max);
	return (tmp[idx]);
}

std::ostream & operator<<(std::ostream & os, hex::direction_t d)
{
	os << to_string(d);
	return (os);
}












/*******************************************************************************
                         ______                     __
                        / ____/___  ____  _________/ /
                       / /   / __ \/ __ \/ ___/ __  /
                      / /___/ /_/ / /_/ / /  / /_/ /
                      \____/\____/\____/_/   \__,_/
                      
*******************************************************************************/






hex::Coord::Coord(int q, int r)
: Coord(q, r, -q - r)
{}

hex::Coord::Coord(int q, int r, int s)
: m_q(q)
, m_r(r)
, m_s(s)
{
  assert(m_q + m_r + m_s == 0);
}

hex::Coord::Coord(FractionalCoord const & oth)
: m_q(static_cast<int>(std::round(oth.q())))
, m_r(static_cast<int>(std::round(oth.r())))
, m_s(static_cast<int>(std::round(oth.s())))
{
  double q_diff = std::abs(m_q - oth.q());
  double r_diff = std::abs(m_r - oth.r());
  double s_diff = std::abs(m_s - oth.s());
  if (q_diff > r_diff && q_diff > s_diff)
  {
      m_q = -m_r - m_s;
  }
  else
  {
    if (r_diff > s_diff)
      m_r = -m_q - m_s;
    else
      m_s = -m_q - m_r;
  }
  assert(m_q + m_r + m_s == 0);
}

hex::Coord::Coord(OffsetCoord const & oth)
: m_q(oth.col() - static_cast<int>((oth.row() + Layout::offset_type * (oth.row() & 1)) / 2))
, m_r(oth.row())
, m_s(-m_q - m_r)
{
  assert(Layout::offset_type == Layout::EVEN || Layout::offset_type == Layout::ODD);
  assert(m_q + m_r + m_s == 0);
}

hex::Coord::Coord(DoubledCoord const & oth)
: m_q(static_cast<int>((oth.col() - oth.row()) / 2))
, m_r(oth.row())
, m_s(-m_q - m_r)
{
  assert(m_q + m_r + m_s == 0);
}






int	hex::Coord::q() const
{
	return (m_q);
}

int	hex::Coord::r() const
{
	return (m_r);
}

int	hex::Coord::s() const
{
	return (m_s);
}






hex::Coord & hex::Coord::operator+=(Coord const & oth)
{
	m_q += oth.m_q;
	m_r += oth.m_r;
	m_s += oth.m_s;

	return (*this);
}

hex::Coord & hex::Coord::operator-=(Coord const & oth)
{
	m_q -= oth.m_q;
	m_r -= oth.m_r;
	m_s -= oth.m_s;

	return (*this);
}

hex::Coord & hex::Coord::operator*=(int k)
{
	m_q *= k;
	m_r *= k;
	m_s *= k;

	return (*this);
}






hex::Coord & hex::Coord::rotate_left()
{
	Coord tmp(*this);
	m_q = -tmp.m_s;
	m_r = -tmp.m_q;
	m_s = -tmp.m_r;

	return (*this);
}

hex::Coord & hex::Coord::rotate_right()
{
	Coord tmp(*this);
	m_q = -tmp.m_r;
	m_r = -tmp.m_s;
	m_s = -tmp.m_q;

	return (*this);
}

hex::Coord hex::Coord::rotate_left() const
{
	Coord tmp;
	tmp.rotate_left();
	return (tmp);
}

hex::Coord hex::Coord::rotate_right() const
{
	Coord tmp;
	tmp.rotate_right();
	return (tmp);
}






hex::Coord hex::Coord::neighbor(direction_t d)
{
	return (coord_directions[static_cast<std::size_t>(d)]);
}

hex::Coord hex::Coord::neighbor(int i)
{
	return (coord_directions[static_cast<std::size_t>(i)]);
}



hex::Coord hex::Coord::neighbor_of(direction_t d) const
{
	return ((*this) + neighbor(d));
}

hex::Coord hex::Coord::neighbor_of(int i) const
{
	return ((*this) + neighbor(i));
}

void hex::Coord::neighbor_of(std::array<Coord, static_cast<std::size_t>(direction_t::__MAX)> & result) const
{
	for (std::size_t i = 0; i < 6; ++i)
		result[i] = neighbor_of(i);
}

void hex::Coord::neighbor_of(std::vector<Coord> & result) const
{
	for (std::size_t i = 0; i < 6; ++i)
		result.emplace_back(neighbor_of(i));
}






int hex::Coord::distance() const
{
  return (static_cast<int>((std::abs(m_q) + std::abs(m_r) + std::abs(m_s)) / 2));
}

int hex::Coord::distance(Coord const & oth) const
{
	return ((oth - (*this)).distance());
}






std::vector<hex::Coord> hex::line(Coord const & a, Coord const & b)
{
	std::vector<hex::Coord> result;

	line(result, a, b);

	return (result);
}

void hex::line(std::vector<Coord> & result, Coord const & a, Coord const & b)
{
		int N = a.distance(b);

    FractionalCoord a_nudge = FractionalCoord(a.q() + 1e-06, a.r() + 1e-06, a.s() - 2e-06);
    FractionalCoord b_nudge = FractionalCoord(b.q() + 1e-06, b.r() + 1e-06, b.s() - 2e-06);
    double step = 1.0 / std::max(N, 1);

    for (int i = 0; i <= N; i++)
      result.emplace_back(lerp(a_nudge, b_nudge, step * i));
}






std::vector<hex::Coord> hex::range(Coord const & center, int N)
{
	std::vector<Coord> result;
	range(result, center, N);
	return (result);
}

void hex::range(std::vector<Coord> & result, Coord const & center, int N)
{
	for (int q = -N; q <= N; ++q)
	{
		for (int r = std::max(-N, -q-N); r <= std::min(N, -q+N); ++r)
			result.emplace_back(center + Coord(q, r, -q - r));
	}
}






std::vector<hex::Coord> hex::ring(Coord const & center, int N)
{
	std::vector<Coord> result;
	ring(result, center, N);
	return (result);
}

void hex::ring(std::vector<Coord> & result, Coord const & center, int N)
{
  if (N == 0)
  {
		result.emplace_back(center);
  	return ;
  }

  Coord tmp = center + (coord_directions[4] * N);
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 1; j < N; ++j)
		{
			result.emplace_back(tmp);
			tmp = tmp.neighbor_of(i);
		}
	}
}






std::vector<hex::Coord> hex::spiral(Coord const & center, int N)
{
	std::vector<Coord> result;
	spiral(result, center, N);
	return (result);
}

void hex::spiral(std::vector<Coord> & result, Coord const & center, int N)
{
  result.emplace_back(center);
  for (int i = 1; i < N; ++i)
    ring(result, center, i);
}









bool operator==(hex::Coord const & left, hex::Coord const & right)
{
	return (left.q() == right.q() && left.r() == right.r() && left.s() == right.s());
}

bool operator!=(hex::Coord const & left, hex::Coord const & right)
{
	return (left.q() != right.q() || left.r() != right.r() || left.s() != right.s());
}

bool operator<(hex::Coord const & left, hex::Coord const & right)
{
	return (left.q() < right.q() && left.r() < right.r() && left.s() < right.s());
}



hex::Coord operator+(hex::Coord const & left, hex::Coord const & right)
{
	hex::Coord res(left);
	res += right;
	return (res);
}

hex::Coord operator-(hex::Coord const & left, hex::Coord const & right)
{
	hex::Coord res(left);
	res -= right;
	return (res);
}


hex::Coord operator*(hex::Coord const & left, int right)
{
	hex::Coord res(left);
	res *= right;
	return (res);
}

hex::Coord operator*(int left, hex::Coord const & right)
{
	return (right * left);
}



std::string to_string(hex::Coord const & c)
{
	std::string result;
	result += std::to_string(c.q());
	result += ", ";
	result += std::to_string(c.r());
	result += ", ";
	result += std::to_string(c.s());
	return (result);	
}

std::ostream & operator<<(std::ostream & os, hex::Coord const & c)
{
	os << c.q() << ", " << c.r() << ", " << c.s();
	return (os);
}












/*******************************************************************************
    ______                __  _                   ________                     __
   / ____/________ ______/ /_(_)___  ____  ____ _/ / ____/___  ____  _________/ /
  / /_  / ___/ __ `/ ___/ __/ / __ \/ __ \/ __ `/ / /   / __ \/ __ \/ ___/ __  /
 / __/ / /  / /_/ / /__/ /_/ / /_/ / / / / /_/ / / /___/ /_/ / /_/ / /  / /_/ /
/_/   /_/   \__,_/\___/\__/_/\____/_/ /_/\__,_/_/\____/\____/\____/_/   \__,_/

*******************************************************************************/






hex::FractionalCoord::FractionalCoord(double q, double r, double s)
: m_q(q)
, m_r(r)
, m_s(s)
{
	assert(std::round(q + r + s) == 0);
}

hex::FractionalCoord::FractionalCoord(Coord const & c)
: m_q(c.q())
, m_r(c.r())
, m_s(c.s())
{
	assert(std::round(m_q + m_r + m_s) == 0);
}

hex::FractionalCoord & hex::FractionalCoord::operator+=(FractionalCoord const & oth)
{
	m_q += oth.m_q;
	m_r += oth.m_r;
	m_s = -m_r -m_q;
	return (*this);
}

hex::FractionalCoord & hex::FractionalCoord::operator-=(FractionalCoord const & oth)
{
	m_q -= oth.m_q;
	m_r -= oth.m_r;
	m_s = -m_r -m_q;
	return (*this);
}

hex::FractionalCoord & hex::FractionalCoord::operator*=(double i)
{
	m_q *= i;
	m_r *= i;
	m_s = -m_r -m_q;
	return (*this);
}


double hex::FractionalCoord::q() const
{
	return (m_q);
}

double hex::FractionalCoord::r() const
{
	return (m_r);
}

double hex::FractionalCoord::s() const
{
	return (m_s);
}


hex::FractionalCoord hex::FractionalCoord::lerp(FractionalCoord const & oth, double t) const
{
  return FractionalCoord(m_q * (1.0 - t) + oth.m_q * t,
                         m_r * (1.0 - t) + oth.m_r * t,
                         m_s * (1.0 - t) + oth.m_s * t);
}





hex::FractionalCoord hex::lerp(FractionalCoord const & a, FractionalCoord const & b, double t)
{
	return (a.lerp(b, t));
}









bool operator==(hex::FractionalCoord const & left, hex::FractionalCoord const & right)
{
	return (left.q() == right.q() && left.r() == right.r() && left.s() == right.s());
}

bool operator!=(hex::FractionalCoord const & left, hex::FractionalCoord const & right)
{
	return (left.q() != right.q() || left.r() != right.r() || left.s() != right.s());
}

bool operator<(hex::FractionalCoord const & left, hex::FractionalCoord const & right)
{
	return (left.q() < right.q() && left.r() < right.r() && left.s() < right.s());
}



hex::FractionalCoord operator+(hex::FractionalCoord const & left, hex::FractionalCoord const & right)
{
	hex::FractionalCoord tmp(left);
	tmp += right;
	return (tmp);
}

hex::FractionalCoord operator-(hex::FractionalCoord const & left, hex::FractionalCoord const & right)
{
	hex::FractionalCoord tmp(left);
	tmp -= right;
	return (tmp);
}


hex::FractionalCoord operator*(hex::FractionalCoord const & left, double right)
{
	hex::FractionalCoord tmp(left);
	tmp *= right;
	return (tmp);
}

hex::FractionalCoord operator*(double left, hex::FractionalCoord const & right)
{
	return (right * left);
}



std::string to_string(hex::FractionalCoord const & c)
{
	std::string result;
	result += std::to_string(c.q());
	result += ", ";
	result += std::to_string(c.r());
	result += ", ";
	result += std::to_string(c.s());
	return (result);	
}

std::ostream & operator<<(std::ostream & os, hex::FractionalCoord const & c)
{
	os << c.q() << ", " << c.r() << ", " << c.s();
	return (os);
}












/*******************************************************************************
              ____  ________          __  ______                     __
             / __ \/ __/ __/__  _____/ /_/ ____/___  ____  _________/ /
            / / / / /_/ /_/ _ \/ ___/ __/ /   / __ \/ __ \/ ___/ __  /
           / /_/ / __/ __/  __(__  ) /_/ /___/ /_/ / /_/ / /  / /_/ /
           \____/_/ /_/  \___/____/\__/\____/\____/\____/_/   \__,_/
           
*******************************************************************************/





hex::OffsetCoord::OffsetCoord(int col, int row)
: m_col(col)
, m_row(row)
{}

hex::OffsetCoord::OffsetCoord(Coord const & oth)
: m_col(oth.q() + int((oth.r() + Layout::offset_type * (oth.r() & 1)) / 2))
, m_row(oth.r())
{}

hex::OffsetCoord::OffsetCoord(FractionalCoord const & oth)
: OffsetCoord(Coord((oth)))
{}


hex::OffsetCoord & hex::OffsetCoord::operator+=(OffsetCoord const & oth)
{
	m_col += oth.m_col;
	m_row += oth.m_row;
	return (*this);

}

hex::OffsetCoord & hex::OffsetCoord::operator-=(OffsetCoord const & oth)
{
	m_col -= oth.m_col;
	m_row -= oth.m_row;
	return (*this);

}


int hex::OffsetCoord::col() const
{
	return (m_col);
}

int hex::OffsetCoord::row() const
{
	return (m_row);
}







bool operator==(hex::OffsetCoord const & left, hex::OffsetCoord const & right)
{
	return (left.col() == right.col() && left.row() == right.row());
}

bool operator!=(hex::OffsetCoord const & left, hex::OffsetCoord const & right)
{
	return (left.col() != right.col() || left.row() != right.row());
}

bool operator<(hex::OffsetCoord const & left, hex::OffsetCoord const & right)
{
	return (left.col() < right.col() && left.row() < right.row());
}



hex::OffsetCoord operator+(hex::OffsetCoord const & left, hex::OffsetCoord const & right)
{
	hex::OffsetCoord tmp(left);
	tmp += right;
	return (tmp);
}

hex::OffsetCoord operator-(hex::OffsetCoord const & left, hex::OffsetCoord const & right)
{
	hex::OffsetCoord tmp(left);
	tmp -= right;
	return (tmp);
}



std::string to_string(hex::OffsetCoord const & c)
{
	std::string result;
	result += std::to_string(c.col());
	result += ", ";
	result += std::to_string(c.row());
	return (result);	
}

std::ostream & operator<<(std::ostream & os, hex::OffsetCoord const & c)
{
	os << c.col() << ", " << c.row();
	return (os);
}












/*******************************************************************************
          ____              __    __         ________                     __
         / __ \____  __  __/ /_  / /__  ____/ / ____/___  ____  _________/ /
        / / / / __ \/ / / / __ \/ / _ \/ __  / /   / __ \/ __ \/ ___/ __  /
       / /_/ / /_/ / /_/ / /_/ / /  __/ /_/ / /___/ /_/ / /_/ / /  / /_/ /
      /_____/\____/\__,_/_.___/_/\___/\__,_/\____/\____/\____/_/   \__,_/
      
*******************************************************************************/




hex::DoubledCoord::DoubledCoord(int col, int row)
: m_col(col)
, m_row(row)
{}

hex::DoubledCoord::DoubledCoord(Coord const & oth)
: m_col(oth.q())
, m_row(2 * oth.r() + oth.q())
{}

hex::DoubledCoord::DoubledCoord(FractionalCoord const & oth)
: DoubledCoord(Coord((oth)))
{}


hex::DoubledCoord & hex::DoubledCoord::operator+=(DoubledCoord const & oth)
{
	m_col += oth.m_col;
	m_row += oth.m_row;
	return (*this);

}

hex::DoubledCoord & hex::DoubledCoord::operator-=(DoubledCoord const & oth)
{
	m_col -= oth.m_col;
	m_row -= oth.m_row;
	return (*this);

}


int hex::DoubledCoord::col() const
{
	return (m_col);
}

int hex::DoubledCoord::row() const
{
	return (m_row);
}







bool operator==(hex::DoubledCoord const & left, hex::DoubledCoord const & right)
{
	return (left.col() == right.col() && left.row() == right.row());
}

bool operator!=(hex::DoubledCoord const & left, hex::DoubledCoord const & right)
{
	return (left.col() != right.col() || left.row() != right.row());
}

bool operator<(hex::DoubledCoord const & left, hex::DoubledCoord const & right)
{
	return (left.col() < right.col() && left.row() < right.row());
}



hex::DoubledCoord operator+(hex::DoubledCoord const & left, hex::DoubledCoord const & right)
{
	hex::DoubledCoord tmp(left);
	tmp += right;
	return (tmp);
}

hex::DoubledCoord operator-(hex::DoubledCoord const & left, hex::DoubledCoord const & right)
{
	hex::DoubledCoord tmp(left);
	tmp -= right;
	return (tmp);
}



std::string to_string(hex::DoubledCoord const & c)
{
	std::string result;
	result += std::to_string(c.col());
	result += ", ";
	result += std::to_string(c.row());
	return (result);	
}

std::ostream & operator<<(std::ostream & os, hex::DoubledCoord const & c)
{
	os << c.col() << ", " << c.row();
	return (os);
}












/*******************************************************************************
                 _       __
                | |     / /________ _____  ____  ___  _____
                | | /| / / ___/ __ `/ __ \/ __ \/ _ \/ ___/
                | |/ |/ / /  / /_/ / /_/ / /_/ /  __/ /
                |__/|__/_/   \__,_/ .___/ .___/\___/_/
                                 /_/   /_/
*******************************************************************************/





hex::Wrapper::Wrapper(bool wrap_horizontaly, bool wrap_verticaly)
: m_wrap_horizontaly(wrap_horizontaly)
, m_wrap_verticaly(wrap_verticaly)
{}


bool hex::Wrapper::wrap_horizontaly() const
{
	return (m_wrap_horizontaly);
}

bool hex::Wrapper::wrap_verticaly() const
{
	return (m_wrap_verticaly);
}


void hex::Wrapper::set_wrap_horizontaly(bool b)
{
	m_wrap_horizontaly = b;
}

void hex::Wrapper::set_wrap_verticaly(bool b)
{
	m_wrap_verticaly = b;
}
