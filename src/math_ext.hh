#ifndef MATH_EXT_HH
#define MATH_EXT_HH


float round_rad(float rad);
float round_deg(float deg);

float rad_to_deg(float rad);
float deg_to_rad(float deg);

float rad_to_arcsec(float rad);
float arcsec_to_rad(float asec);

float deg_to_arcsec(float deg);
float arcsec_to_deg(float asec);


float naive_lerp(float a, float b, float c);

float angular_size_rad(float object_cross_section, float distance);

bool is_in_angle_rad(float azimut_to_test, float azimut_target, float range);
bool is_in_angle_deg(float azimut_to_test, float azimut_target, float range);



#endif // MATH_EXT_HH