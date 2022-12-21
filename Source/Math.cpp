#include "Math.h"


float random_float01()
{
	return rand() / static_cast<float>(RAND_MAX);
}

float random_float_in_range(float min, float max)
{
	return random_float01() * (max - min) + min;
}

// To be used for rock direction

Vector2 random_direction_pi()
{
	float angle = random_float01()* PI;
	return Vector2(cos(angle), sin(angle));
}