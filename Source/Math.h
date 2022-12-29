#pragma once
#include <cmath>
#include "raylib.h"

float random_float01();

float random_float_in_range(float min, float max);

Vector2 random_direction();

int rock_spawnrate(int point_count, int rock_cooldown);