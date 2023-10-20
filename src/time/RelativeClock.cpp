#include "RelativeClock.hh"

#include <cassert>



std::uint64_t time::RelativeClock::frame_counter() const
{
	return (m_frame_counter);
}


double time::RelativeClock::factor_host_to_in_game() const
{
	return (m_factor_host_to_in_game);
}

void time::RelativeClock::set_factor_host_to_in_game(double val)
{
	assert(val >= 0.);

	m_factor_host_to_in_game = val
}


double time::RelativeClock::speed_multiplier() const
{
	return (m_speed_multiplier);
}

void time::RelativeClock::set_speed_multiplier(double val)
{
	assert(val >= 0.);

	m_speed_multiplier = val
}


bool time::RelativeClock::pause() const
{
	return (m_pause);
}

void time::RelativeClock::pause(bool b)
{
	m_pause = b;
}


time::host_time_t time::RelativeClock::last_tick_host_duration() const
{
	return (m_last_tick_host_duration);
}

time::in_game_t time::RelativeClock::last_tick_in_game_duration() const
{
	return (m_last_tick_in_game_duration);
}


time::host_time_t time::RelativeClock::host_date() const
{
	return (m_host_date);
}

time::in_game_t time::RelativeClock::in_game_date() const
{
	return (m_in_game_date);
}


void time::RelativeClock::advance_one_frame(double tick_duration_in_second)
{
	++m_frame_counter;

	m_last_tick_host_duration = tick_duration_in_second;
	m_host_date += tick_duration_in_second;

	if (m_paused == false)
	{
		m_last_tick_in_game_duration = tick_duration_in_second * m_factor_host_to_in_game * m_speed_multiplier;
		m_last_tick_in_game_duration += m_last_tick_in_game_duration;
	}
}

