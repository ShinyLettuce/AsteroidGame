#include "Math.h"

Vector2 normalize(float vect_x, float vect_y)
{
	float length = sqrt(vect_x * vect_x + vect_y * vect_y);
	if (length > FLT_EPSILON) // FLT_EPSILON because we want to avoid using zero
	{
		return{ vect_x /= length, vect_y /= length };
	}
}

float random_float01()
{
	return rand() / static_cast<float>(RAND_MAX);
}

float random_float_in_range(float min, float max)
{
	return random_float01() * (max - min) + min;
}

Vector2 random_direction()
{
	float angle = random_float_in_range(PI/8.f,(3*PI)/4.f );
	return normalize(cosf(angle), sinf(angle) +3);
}

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

bool collision(Vector2 a_pos, Vector2 b_pos, int a_size, int b_size)
{
	return a_pos.x <= b_pos.x + b_size &&
		   a_pos.x + a_size >= b_pos.x &&
	   	   a_pos.y + a_size >= b_pos.y &&
		   a_pos.y <= b_pos.y + b_size;
}
