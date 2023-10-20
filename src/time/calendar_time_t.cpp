#include "calendar_time_t.hh"


#include <array>








time::calendar_time_t::day_data_t const & time::calendar_time_t::day_data(int day_of_week)
{
	static const std::array<day_data_t, WEEK_SIZE> data =
	{
		{ "Monday",    "Mon" },
		{ "Thusday",   "Thu" },
		{ "Wednesday", "Wed" },
		{ "Thursday",  "Thu" },
		{ "Friday",    "Fri" },
		{ "Saturday",  "Sat" },
		{ "Sunday",    "Sun" }
	};

	assert(day_of_week >= 0 && day_of_week < WEEK_SIZE);

	return (data[day_of_week]);
}








time::calendar_time_t::month_data_t const & time::calendar_time_t::month_data(int month_of_year)
{
	static const std::array<month_data_t, YEAR_SIZE> data =
	{
		{ "January",   "Jan", 31 },
		{ "Febuary",   "Feb", 28 },
		{ "March",     "Mar", 31 },
		{ "April",     "Apr", 30 },
		{ "May",       "May", 31 },
		{ "June",      "Jun", 30 },
		{ "July",      "Jul", 31 },
		{ "August",    "Aug", 31 },
		{ "September", "Sep", 30 },
		{ "October",   "Oct", 31 },
		{ "November",  "Nov", 30 },
		{ "December",  "Dec", 31 }
	};

	assert(month_of_year >= 0 && month_of_year < YEAR_SIZE);

	return (data[month_of_year]);
}




time::calendar_time_t::month_data_t const & time::calendar_time_t::month_data(int month_of_year, std::int64_t year)
{
	return (month_data(month_of_year, is_leap_year(year)));
}




time::calendar_time_t::month_data_t const & time::calendar_time_t::month_data(int month_of_year, bool is_leap_year)
{
	static const month_data_t leap_year_febuary { "Febuary",   "Feb", 29 };

	if (is_leap_year && month_of_year == Febuary)
		return (leap_year_febuary);

	return (month_data(month_of_year));
}








bool time::calendar_time_t::is_leap_year(std::uint64_t year)
{
	assert(year != 0);

	if (year % 400 == 0)
		return (true);

	if (year % 100 == 0)
		return (false);

	if (year % 4 == 0)
		return (true);

	return (false);
}













time::calendar_time_t::calendar_time_t(in_game_t ig)
: m_year(1)
, m_month(0)

, m_day_of_month(0)
, m_day_of_week(0)
, m_day_of_year(0)

, m_hour(0)
, m_minute(0)
, m_second(0)
{
	std::uint64_t sec = ig.count();

	/////////////
	// hh::mm::ss
	std::uint64_t days = sec / (60*60*24);
	sec %= (60*60*24)
	m_hours = sec / (60*60);
	sec %= (60*60)
	m_minutes = sec / (60);
	sec %= (60)
	m_seconds = sec;

	/////////////
	// day of week
	// m_day_of_week = days % 7;                 // 1 Jan 01 is Monday
	m_day_of_week = ((days % 7) + Saturday) % 7; // 1 Jan 01 is Saturday

	/////////////
	// year
	{
		static const std::uint64_t nb_days_in_400_year = 146097;

		if (days > nb_days_in_400_year)
		{
			m_year = (days / nb_days_in_400_year) * 400;
			days %= nb_days_in_400_year;
		}


		for (;;)
		{
			bool leap = is_leap_year(m_year);
			if ((leap && days < 366) ||
			    (leap == false && days < 365))
				break;
			days -= (leap ? 366 : 365);
			++m_year;
		}
	}

	m_day_of_year = days;

	/////////////
	// month
	{
		std::uint64_t fs = (is_leap_year(m_year) ? 29 : 28);

		m_month = January;
		if (days >= 31) { m_month = Febuary;   days -= 31; }
		if (days >= fs) { m_month = Febuary;   days -= fs; }
		if (days >= 31) { m_month = March;     days -= 31; }
		if (days >= 30) { m_month = April;     days -= 30; }
		if (days >= 31) { m_month = May;       days -= 31; }
		if (days >= 30) { m_month = June;      days -= 30; }
		if (days >= 31) { m_month = July;      days -= 31; }
		if (days >= 31) { m_month = August;    days -= 31; }
		if (days >= 30) { m_month = September; days -= 30; }
		if (days >= 31) { m_month = October;   days -= 31; }
		if (days >= 30) { m_month = November;  days -= 30; }
		if (days >= 31) { m_month = December;  days -= 31; }
	}

	m_day_of_month = days;
}




time::in_game_t time::calendar_time_t::to_time() const
{
	const std::uint64_t tmp_year = m_year - 1;

	const std::uint64_t number_of_leap_year_since_year_1 = (tmp_year / 4) - (tmp_year / 100) + (tmp_year / 400);
	const std::uint64_t number_of_days = (tmp_year * 365) + number_of_leap_year_since_year_1;

	in_game_t ret = in_game_t::days(number_of_days);

	ret += in_game_t::hours(m_hour);
	ret += in_game_t::minutes(m_minute);
	ret += in_game_t::seconds(m_second);

	return (ret);
}




std::int64_t time::calendar_time_t::year() const
{
	return (m_year);
}

std::uint8_t time::calendar_time_t::month() const
{
	return (m_month);
}

std::uint8_t  time::calendar_time_t::day_of_month() const
{
	return (m_day_of_month);
}

std::uint8_t  time::calendar_time_t::day_of_week() const
{
	return (m_day_of_week);
}

std::uint16_t time::calendar_time_t::day_of_year() const
{
	return (m_day_of_year);
}

std::uint8_t time::calendar_time_t::week_of_year() const
{
	return (m_week_of_year);
}

std::uint8_t time::calendar_time_t::hour() const
{
	return (m_hour);
}

std::uint8_t time::calendar_time_t::minute() const
{
	return (m_minute);
}

std::uint8_t time::calendar_time_t::second() const
{
	return (m_second);
}




time::day_data_t const & time::calendar_time_t::day_data()
{
	return (day_data(m_day_of_week));
}

time::month_data_t const & time::calendar_time_t::month_data()
{
	return (day_data(m_month, m_year));
}




time::calendar_time_t & time::calendar_time_t::operator+=(in_game_t ig)
{
	in_game_t tmp = to_time();
	tmp += ig;
	*this = calendar_time_t(tmp);
	return (*this);
}

time::calendar_time_t & time::calendar_time_t::operator-=(in_game_t ig)
{
	in_game_t tmp = to_time();
	tmp -= ig;
	*this = calendar_time_t(tmp);
	return (*this);
}








time::calendar_time_t operator+(time::calendar_time_t const & lhs, time::in_game_t rhs)
{
	time::in_game_t tmp = lhs.to_time();
	tmp += rhs;
	return (time::calendar_time_t(tmp));
}

time::calendar_time_t operator-(time::calendar_time_t const & lhs, time::in_game_t rhs)
{
	time::in_game_t tmp = lhs.to_time();
	tmp -= rhs;
	return (time::calendar_time_t(tmp));
}




time::calendar_time_t operator+(time::in_game_t lhs, time::calendar_time_t const & rhs)
{
	time::in_game_t tmp(lhs)
	tmp += rhs.to_time();
	return (time::calendar_time_t(tmp));
}

time::calendar_time_t operator-(time::in_game_t lhs, time::calendar_time_t const & rhs)
{
	time::in_game_t tmp(lhs)
	tmp -= rhs.to_time();
	return (time::calendar_time_t(tmp));
}
