#pragma once
#include <cmath>
#include "raylib.h"

// Normalizes two vectors
Vector2 normalize(float vect_x, float vect_y);

// returns random value between 0 and 1
float random_float01();

// To be used for rock spawn position
float random_float_in_range(float min, float max);

// To be used for rock direction
Vector2 random_direction();

// Changes spawn rate based on initial spawnrate and current score
int rock_spawnrate(int point_count, int rock_cooldown);

// Checks for collision between two boxes and returns true on collision
bool collision(Vector2 a_pos, Vector2 b_pos, int a_size, int b_size);

