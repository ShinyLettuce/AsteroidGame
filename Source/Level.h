#pragma once
#include "Entity.h"
#include <list>

class Level
{
public:
	Player mario;
	Projectile shot;
	std::list<Rock> all_rocks = {};  // using list since that has the member function remove_if
	std::list<Coin> all_coins = {};

	// Vector2 size;

	int rock_timer = 0;

	void spawn_rock();
	void spawn_projectile();
	void spawn_coin(Rock rock); // TODO: try implementing entity pool

	void remove_dead_rocks();
	void remove_dead_coins();  // TODO: make these into one function

	void level_init();

	void update();
	void render();
};