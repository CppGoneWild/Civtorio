#ifndef RELATIVECLOCK_HH
#define RELATIVECLOCK_HH



#include <cstdint>

#include "in_game_t.hh"



namespace time
{


using host_time_t = double;


class RelativeClock
{
public:
	RelativeClock()                      = default;
	RelativeClock(RelativeClock const &) = default;
	RelativeClock(RelativeClock &&)      = default;
	~RelativeClock()                     = default;

	RelativeClock & operator=(RelativeClock const &) = default;
	RelativeClock & operator=(RelativeClock &&)      = default;

	std::uint64_t frame_counter() const;

	double factor_host_to_in_game() const;
	void set_factor_host_to_in_game(double);

	double speed_multiplier() const;
	void set_speed_multiplier(double);

	bool pause() const;
	void pause(bool);

	host_time_t last_tick_host_duration() const;
	in_game_t   last_tick_in_game_duration() const;

	host_time_t host_date() const;
	in_game_t   in_game_date() const;

	void advance_one_frame(double tick_duration_in_second);

private:

	std::uint64_t m_frame_counter = 0;

	double m_factor_host_to_in_game = 1440.0; // 1 day in_game = 1 minute host_time

	double m_speed_multiplier = 1.0;
	bool   m_paused = false;

	host_time_t m_last_tick_host_duration    = 0;
	in_game_t   m_last_tick_in_game_duration = 0;

	host_time_t m_host_date    = 0;
	in_game_t   m_in_game_date = 0;
};


} // time


#endif // RELATIVECLOCK_HH