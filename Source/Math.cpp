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

// Changes spawn rate based on current score and initial spawnrate
int rock_spawnrate(int point_count, int rock_cooldown)
{
	if (point_count < 5000)
	{
		return (rock_cooldown - 10 * (point_count / 1000));
	}
	else
	{
		return (rock_cooldown - 20 - 5 * (point_count / 1000));
	}
}