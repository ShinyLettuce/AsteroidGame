#pragma once
#include "Entity.h"
#include <list>

class Level
{
public:
	Player mario;
	std::list<Rock> all_rocks = {};  // using list since that has the member function remove_if
	Projectile shot;

	// Vector2 size;

	int rock_timer = 0;

	void spawn_rock(const Rock& rock);
	void spawn_projectile();

	void remove_dead_rocks();

	void level_init();

	void update();
	void render();
};