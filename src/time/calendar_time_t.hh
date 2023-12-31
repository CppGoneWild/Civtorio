#ifndef CALENDAR_TIME_T_HH
#define CALENDAR_TIME_T_HH



#include "in_game_t.hh"

#include <cstdint>



namespace time
{


class calendar_time_t
{
public:
	enum day_e : std::uint64_t
	{
		Monday    = 0,
		Thusday   = 1,
		Wednesday = 2,
		Thursday  = 3,
		Friday    = 4,
		Saturday  = 5,
		Sunday    = 6,

		WEEK_SIZE = 7
	};

	enum month_e : std::uint64_t
	{
		January   = 0,
		Febuary   = 1,
		March     = 2,
		April     = 3,
		May       = 4,
		June      = 5,
		July      = 6,
		August    = 7,
		September = 8,
		October   = 9,
		November  = 10,
		December  = 11,

		YEAR_SIZE = 12
	};

	struct day_data_t
	{
		char long_name[12];
		char short_name[4];
	};
	static day_data_t const & day_data(int day_of_week);

	struct month_data_t
	{
		char long_name[12];
		char short_name[4];
		std::uint8_t nb_days;
	};
	static month_data_t const & month_data(int month_of_year);
	static month_data_t const & month_data(int month_of_year, std::int64_t year);
	static month_data_t const & month_data(int month_of_year, bool is_leap_year);

	static bool is_leap_year(std::uint64_t); //  /!\ start at 1


	calendar_time_t(in_game_t);

	in_game_t to_time() const;


	std::int64_t year() const; //  /!\ start at 1
	std::uint8_t month() const;

	std::uint8_t  day_of_month() const;
	std::uint8_t  day_of_week() const;
	std::uint16_t day_of_year() const;

	std::uint8_t hour() const;
	std::uint8_t minute() const;
	std::uint8_t second() const;

	day_data_t const & day_data();
	month_data_t const & month_data();


	calendar_time_t & operator+=(in_game_t);
	calendar_time_t & operator-=(in_game_t);

private:
	std::int64_t m_year  = 1; //  /!\ start at 1
	std::uint8_t m_month = 0;

	std::uint8_t  m_day_of_month = 0;
	std::uint8_t  m_day_of_week  = 0;
	std::uint16_t m_day_of_year  = 0;

	std::uint8_t m_hour   = 0;
	std::uint8_t m_minute = 0;
	std::uint8_t m_second = 0;
};



} // time


time::calendar_time_t operator+(time::calendar_time_t const &, time::in_game_t);
time::calendar_time_t operator-(time::calendar_time_t const &, time::in_game_t);

time::calendar_time_t operator+(time::in_game_t, time::calendar_time_t const &);
time::calendar_time_t operator-(time::in_game_t, time::calendar_time_t const &);



#endif // CALENDAR_TIME_T_HH