#ifndef CALENDAR_DURATION_T_HH
#define CALENDAR_DURATION_T_HH



#include "in_game_t.hh"

#include <cstdint>



namespace time
{


class calendar_duration_t
{
public:
	calendar_duration_t()                            = default;
	calendar_duration_t(calendar_duration_t const &) = default;
	calendar_duration_t(calendar_duration_t &&)      = default;
	~calendar_duration_t()                           = default;

	calendar_duration_t & operator=(calendar_duration_t const &) = default;
	calendar_duration_t & operator=(calendar_duration_t &&)      = default;

	calendar_duration_t(in_game_t);
	calendar_duration_t & operator=(in_game_t);

	in_game_t to_time() const;

	std::uint64_t years() const;
	std::uint8_t  months() const;
	std::uint8_t  days_of_month() const;
	std::uint8_t  hours() const;
	std::uint8_t  minutes() const;
	std::uint8_t  seconds() const;

private:
	std::uint64_t m_years  = 0;
	std::uint8_t  m_months = 0;
	std::uint8_t  m_days_of_month = 0; // 30 days
	std::uint8_t  m_hours   = 0;
	std::uint8_t  m_minutes = 0;
	std::uint8_t  m_seconds = 0;
};


} // time


#endif // CALENDAR_DURATION_T_HH