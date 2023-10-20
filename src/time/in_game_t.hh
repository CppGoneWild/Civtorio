#ifndef IN_GAME_T_HH
#define IN_GAME_T_HH



#include <cstdint>



namespace time
{



class calendar_t;
class calendar_duration_t;



class in_game_t
{
public:
	in_game_t()                  = default;
	in_game_t(in_game_t const &) = default;
	in_game_t(in_game_t &&)      = default;
	~in_game_t()                 = default;

	in_game_t & operator=(in_game_t const &) = default;
	in_game_t & operator=(in_game_t &&)      = default;

	in_game_t(std::uint64_t);
	in_game_t(calendar_t const &);
	in_game_t(calendar_duration_t const &);

	in_game_t & operator=(std::uint64_t);
	in_game_t & operator=(calendar_t const &);
	in_game_t & operator=(calendar_duration_t const &);


	bool operator==(std::uint64_t) const;
	bool operator!=(std::uint64_t) const;
	bool operator> (std::uint64_t) const;
	bool operator< (std::uint64_t) const;
	bool operator>=(std::uint64_t) const;
	bool operator<=(std::uint64_t) const;


	bool operator==(in_game_t) const;
	bool operator!=(in_game_t) const;
	bool operator> (in_game_t) const;
	bool operator< (in_game_t) const;
	bool operator>=(in_game_t) const;
	bool operator<=(in_game_t) const;


	in_game_t & operator++();
	in_game_t operator++(int) const;

	in_game_t & operator--();
	in_game_t operator--(int) const;


	in_game_t & operator+=(in_game_t);
	in_game_t & operator-=(in_game_t);

	in_game_t & operator+=(std::uint64_t);
	in_game_t & operator-=(std::uint64_t);


	in_game_t & operator*=(int);
	in_game_t & operator/=(int);

	in_game_t & operator*=(double);
	in_game_t & operator/=(double);


	std::uint64_t count() const;
	std::uint64_t & count();


	std::uint64_t as_seconds() const;
	double as_minutes() const;
	double as_hours() const;
	double as_days() const;
	double as_weeks() const;
	double as_years() const;


	static in_game_t seconds(std::uint64_t);
	static in_game_t minutes(double);
	static in_game_t hours(double);
	static in_game_t days(double);
	static in_game_t weeks(double);
	static in_game_t years(double);


private:
	std::uint64_t m_seconds_counter = 0;
};



} // time



bool operator==(std::uint64_t, time::in_game_t);
bool operator!=(std::uint64_t, time::in_game_t);
bool operator> (std::uint64_t, time::in_game_t);
bool operator< (std::uint64_t, time::in_game_t);
bool operator>=(std::uint64_t, time::in_game_t);
bool operator<=(std::uint64_t, time::in_game_t);



time::in_game_t operator+(time::in_game_t, time::in_game_t);
time::in_game_t operator-(time::in_game_t, time::in_game_t);


time::in_game_t operator+(std::uint64_t, time::in_game_t);
time::in_game_t operator-(std::uint64_t, time::in_game_t);


time::in_game_t operator+(time::in_game_t, std::uint64_t);
time::in_game_t operator-(time::in_game_t, std::uint64_t);


time::in_game_t operator*(time::in_game_t, int);
time::in_game_t operator/(time::in_game_t, int);


time::in_game_t operator*(time::in_game_t, double);
time::in_game_t operator/(time::in_game_t, double);



#endif // IN_GAME_T_HH