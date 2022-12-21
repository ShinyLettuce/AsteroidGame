#include "Math.h"

float random_float01()
{
	return rand() / static_cast<float>(RAND_MAX);
}

// To be used for rock spawn position

float random_float_in_range(float min, float max)
{
	return random_float01() * (max - min) + min;
}

// To be used for rock direction

Vector2 random_direction()
{
	float angle = random_float_in_range(PI/4.f,(3.f*PI)/4.f );
	return Vector2(cos(angle), sin(angle));
}