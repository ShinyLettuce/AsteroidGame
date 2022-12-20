#pragma once
#include "Entity.h"
#include <vector>

class Level
{
public:
	Player mario;
	std::vector<Rock> all_rocks = {};
	Projectile shot;

	Vector2 size;

	int rock_timer = 0;

	void spawn_rock(const Rock& rock);
	void spawn_projectile();

	void update();
	void render();
};