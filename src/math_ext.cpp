#include "math_ext.hh"

#define _USE_MATH_DEFINES
#include <cmath>
#include <cassert>



float round_rad(float rad)
{
	return std::fmod(rad, M_PI);
	if (rad < 0.f)
		rad -= M_PI;
	return (rad);
}

float round_deg(float deg)
{
	return std::fmod(deg, 360.f);
	if (deg < 0.f)
		deg -= 360.f;
	return (deg);
}



float rad_to_deg(float rad)
{
	return (rad * (180.f / M_PI));
}

float deg_to_rad(float deg)
{
	return (deg * (M_PI / 180.f));
}



float rad_to_arcsec(float rad)
{
	return (rad * ((180.f * 3600.f) / M_PI));
}

float arcsec_to_rad(float asec)
{
	return (asec * (M_PI / (180.f * 3600.f)));
}




float deg_to_arcsec(float deg)
{
	return (deg * 3600.f);
}

float arcsec_to_deg(float asec)
{
	return (asec / 3600.f);
}





float naive_lerp(float a, float b, float c)
{
	return (a + c * (b - a));
}



float angular_size_rad(float object_cross_section, float distance)
{
	assert(distance > 0.f);

	if (distance > 3 * object_cross_section)
		return (object_cross_section / distance);
	return (2.f * std::atan(object_cross_section / (2.f * distance)));
}



bool is_in_angle_rad(float azimut_to_test, float azimut_target, float range)
{
	static const float __end_of_first_quad = M_PI / 2.f;
	static const float __start_of_last_quad = (3.f * M_PI) / 4.f;
	static const float __end_of_last_quad = 2.f * M_PI;

	assert(range >= 0);

	if (range >= __end_of_last_quad)
		return (true);

	if (range > M_PI)
		return (!is_in_angle_rad(azimut_to_test, azimut_target + M_PI, __end_of_last_quad - range));

	if (range == 0.f)
	{
		azimut_to_test = round_rad(azimut_to_test);
		azimut_target = round_rad(azimut_target);
		return (azimut_to_test == azimut_target);
	}

	float start = round_rad(azimut_target - range);
	float end = round_rad(azimut_target + range);

	if (end < start)
		std::swap(start, end);

	if (end > __start_of_last_quad && start < __end_of_first_quad)
	{
		float offset = __end_of_last_quad - end;
		end = 0.f;
		start += offset;
		azimut_to_test = round_rad(azimut_to_test + offset);
		return (azimut_to_test < start);
	}

	azimut_to_test = round_rad(azimut_to_test);

	return (azimut_to_test > start && azimut_to_test < end);
}


bool is_in_angle_deg(float azimut_to_test, float azimut_target, float range)
{
	assert(range >= 0);

	if (range >= 360.f)
		return (true);

	if (range > 180.f)
		return (!is_in_angle_deg(azimut_to_test, azimut_target + 180.f, 360.f - range));

	if (range == 0.f)
	{
		azimut_to_test = round_deg(azimut_to_test);
		azimut_target = round_deg(azimut_target);
		return (azimut_to_test == azimut_target);
	}

	static const float __end_of_first_quad = 90.f;
	static const float __start_of_last_quad = 360.f - 90.f;
	static const float __end_of_last_quad = 360.f;

	float start = round_deg(azimut_target - range);
	float end = round_deg(azimut_target + range);

	if (end < start)
		std::swap(start, end);

	if (end > __start_of_last_quad && start < __end_of_first_quad)
	{
		float offset = __end_of_last_quad - end;
		end = 0.f;
		start += offset;
		azimut_to_test = round_deg(azimut_to_test + offset);
		return (azimut_to_test < start);
	}

	azimut_to_test = round_deg(azimut_to_test);

	return (azimut_to_test > start && azimut_to_test < end);
}

