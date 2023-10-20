#include "calendar_duration_t.hh"




time::calendar_duration_t::calendar_duration_t(in_game_t ig)
: m_years()
, m_months()
, m_days_of_month()
, m_hours()
, m_minutes()
, m_seconds()
{
	std::uint64_t sec = ig.count();

	m_years = sec / (60*60*24*365);
	sec %= (60*60*24*365)

	m_months = sec / (60*60*24*30);
	sec %= (60*60*24*30)

	m_days_of_month = sec / (60*60*24);
	sec %= (60*60*24)

	m_hours = sec / (60*60);
	sec %= (60*60)

	m_minutes = sec / (60);
	sec %= (60)

	m_seconds = sec;
}




time::calendar_duration_t & time::calendar_duration_t::operator=(in_game_t ig)
{
	*this = calendar_duration_t(ig);
	return (*this);
}




time::in_game_t time::calendar_duration_t::to_time() const
{
	in_game_t ret = in_game_t::years(m_years);

	ret += in_game_t::days(m_months * 30);
	ret += in_game_t::days(m_days_of_month);
	ret += in_game_t::hours(m_hours);
	ret += in_game_t::minutes(m_minutes);
	ret += in_game_t::seconds(m_seconds);

	return (ret);
}




std::uint64_t time::calendar_duration_t::years() const
{
	return (m_years);
}

std::uint8_t  time::calendar_duration_t::months() const
{
	return (m_months);
}

std::uint8_t  time::calendar_duration_t::days_of_month() const
{
	return (m_days_of_month);
}

std::uint8_t  time::calendar_duration_t::hours() const
{
	return (m_hours);
}

std::uint8_t  time::calendar_duration_t::minutes() const
{
	return (m_minutes);
}

std::uint8_t  time::calendar_duration_t::seconds() const
{
	return (m_seconds);
}
