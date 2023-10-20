#include "in_game_t.hh"

#include "calendar_t.hh"
#include "calendar_duration_t.hh"



time::in_game_t::in_game_t(std::uint64_t c)
: m_seconds_counter(c)
{}

time::in_game_t::in_game_t(calendar_t const & c)
: in_game_t(c.to_time())
{}

time::in_game_t::in_game_t(calendar_duration_t const & c)
: in_game_t(c.to_time())
{}


time::in_game_t & time::in_game_t::operator=(std::uint64_t oth)
{
	m_seconds_counter = oth;
	return (*this);
}

time::in_game_t & time::in_game_t::operator=(calendar_t const & oth)
{
	*this = oth.to_time();
	return (*this);
}

time::in_game_t & time::in_game_t::operator=(calendar_duration_t const & oth)
{
	*this = oth.to_time();
	return (*this);
}








bool time::in_game_t::operator==(std::uint64_t i) const
{
	return (m_seconds_counter == i);
}

bool time::in_game_t::operator!=(std::uint64_t i) const
{
	return (m_seconds_counter != i);
}

bool time::in_game_t::operator> (std::uint64_t i) const
{
	return (m_seconds_counter >  i);
}

bool time::in_game_t::operator< (std::uint64_t i) const
{
	return (m_seconds_counter <  i);
}

bool time::in_game_t::operator>=(std::uint64_t i) const
{
	return (m_seconds_counter >= i);
}

bool time::in_game_t::operator<=(std::uint64_t i) const
{
	return (m_seconds_counter <= i);
}



bool time::in_game_t::operator==(in_game_t oth) const
{
	return (m_seconds_counter == oth.count());
}

bool time::in_game_t::operator!=(in_game_t oth) const
{
	return (m_seconds_counter != oth.count());
}

bool time::in_game_t::operator> (in_game_t oth) const
{
	return (m_seconds_counter >  oth.count());
}

bool time::in_game_t::operator< (in_game_t oth) const
{
	return (m_seconds_counter <  oth.count());
}

bool time::in_game_t::operator>=(in_game_t oth) const
{
	return (m_seconds_counter >= oth.count());
}

bool time::in_game_t::operator<=(in_game_t oth) const
{
	return (m_seconds_counter <= oth.count());
}



time::in_game_t & time::in_game_t::operator++()
{
	++m_seconds_counter;
	return (*this);
}

time::in_game_t time::in_game_t::operator++(int) const
{
	in_game_t tmp(*this);
	++m_seconds_counter;
	return (tmp);	
}


time::in_game_t & time::in_game_t::operator--()
{
	--m_seconds_counter;
	return (*this);
}

time::in_game_t time::in_game_t::operator--(int) const
{
	in_game_t tmp(*this);
	--m_seconds_counter;
	return (tmp);	
}



time::in_game_t & time::in_game_t::operator+=(in_game_t ig)
{
	*this += ig.count();
	return (*this);
}

time::in_game_t & time::in_game_t::operator-=(in_game_t ig)
{
	*this -= ig.count();
	return (*this);
}


time::in_game_t & time::in_game_t::operator+=(std::uint64_t c)
{
	m_seconds_counter += c;
	return (*this);
}

time::in_game_t & time::in_game_t::operator-=(std::uint64_t c)
{
	if (c > m_seconds_counter)
		m_seconds_counter = 0;
	else
		m_seconds_counter -= c;
	return (*this);
}



time::in_game_t & time::in_game_t::operator*=(int i)
{
	if (i < 0)
		m_seconds_counter = 0;
	else
		m_seconds_counter *= i;
	return (*this);
}

time::in_game_t & time::in_game_t::operator/=(int i)
{
	if (i < 0)
		m_seconds_counter = 0;
	else
		m_seconds_counter /= i;
	return (*this);
}


time::in_game_t & time::in_game_t::operator*=(double i)
{
	if (i < 0.)
		m_seconds_counter = 0;
	else
		m_seconds_counter *= i;
	return (*this);
}

time::in_game_t & time::in_game_t::operator/=(double i)
{
	if (i < 0.)
		m_seconds_counter = 0;
	else
		m_seconds_counter /= i;
	return (*this);
}



std::uint64_t time::in_game_t::count() const
{
	return (m_seconds_counter);
}

std::uint64_t & time::in_game_t::count()
{
	return (m_seconds_counter);
}



std::uint64_t time::in_game_t::as_seconds() const
{
	return (m_seconds_counter);
}

double time::in_game_t::as_minutes() const
{
	return (static_cast<double>(m_seconds_counter) / (60.));
}

double time::in_game_t::as_hours() const
{
	return (static_cast<double>(m_seconds_counter) / (60. * 60.));
}

double time::in_game_t::as_days() const
{
	return (static_cast<double>(m_seconds_counter) / (60. * 60. * 24.));
}

double time::in_game_t::as_weeks() const
{
	return (static_cast<double>(m_seconds_counter) / (60. * 60. * 24. * 7.));
}

double time::in_game_t::as_years() const
{
	return (static_cast<double>(m_seconds_counter) / (60. * 60. * 24. * 365.));
}



time::in_game_t time::in_game_t::seconds(std::uint64_t i)
{
	return (in_game_t(i));
}

time::in_game_t time::in_game_t::minutes(double i)
{
	return (in_game_t(i * 60));
}

time::in_game_t time::in_game_t::hours(double i)
{
	return (in_game_t(i * 60 * 60));
}

time::in_game_t time::in_game_t::days(double i)
{
	return (in_game_t(i * 60 * 60 * 24));
}

time::in_game_t time::in_game_t::weeks(double i)
{
	return (in_game_t(i * 60 * 60 * 24 * 7));
}

time::in_game_t time::in_game_t::years(double i)
{
	return (in_game_t(i * 60 * 60 * 24 * 365));
}












bool operator==(std::uint64_t lhs, time::in_game_t rhs)
{
	return (lhs == rhs.count());
}

bool operator!=(std::uint64_t lhs, time::in_game_t rhs)
{
	return (lhs != rhs.count());
}

bool operator> (std::uint64_t lhs, time::in_game_t rhs)
{
	return (lhs >  rhs.count());
}

bool operator< (std::uint64_t lhs, time::in_game_t rhs)
{
	return (lhs <  rhs.count());
}

bool operator>=(std::uint64_t lhs, time::in_game_t rhs)
{
	return (lhs >= rhs.count());
}

bool operator<=(std::uint64_t lhs, time::in_game_t rhs)
{
	return (lhs <= rhs.count());
}




time::in_game_t operator+(time::in_game_t lhs, time::in_game_t rhs)
{
	in_game_t tmp(lhs);
	tmp += rhs;
	return (tmp);
}

time::in_game_t operator-(time::in_game_t lhs, time::in_game_t rhs)
{
	in_game_t tmp(lhs);
	tmp -= rhs;
	return (tmp);
}



time::in_game_t operator+(std::uint64_t lhs, time::in_game_t rhs)
{
	in_game_t tmp(lhs);
	tmp += rhs;
	return (tmp);
}

time::in_game_t operator-(std::uint64_t lhs, time::in_game_t rhs)
{
	in_game_t tmp(lhs);
	tmp -= rhs;
	return (tmp);
}



time::in_game_t operator+(time::in_game_t lhs, std::uint64_t rhs)
{
	in_game_t tmp(lhs);
	tmp += rhs;
	return (tmp);
}

time::in_game_t operator-(time::in_game_t lhs, std::uint64_t rhs)
{
	in_game_t tmp(lhs);
	tmp -= rhs;
	return (tmp);
}



time::in_game_t operator*(time::in_game_t lhs, int rhs)
{
	in_game_t tmp(lhs);
	tmp *= rhs;
	return (tmp);
}

time::in_game_t operator/(time::in_game_t lhs, int rhs)
{
	in_game_t tmp(lhs);
	tmp /= rhs;
	return (tmp);
}



time::in_game_t operator*(time::in_game_t lhs, double rhs)
{
	in_game_t tmp(lhs);
	tmp *= rhs;
	return (tmp);
}

time::in_game_t operator/(time::in_game_t lhs, double rhs)
{
	in_game_t tmp(lhs);
	tmp /= rhs;
	return (tmp);
}
