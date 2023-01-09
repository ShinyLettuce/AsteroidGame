#pragma once
#include "Entity.h"
#include <list>

class Level
{
public:
	Sound menusound;
	Sound death;
	Sound collectible;

	Player mario;
	Projectile shot;
	std::list<Rock> all_rocks		  = {};  // using list since that has the member function remove_if
	std::list<Coin> all_coins         = {};
	std::list<Particle> all_particles = {};

	// Vector2 size;
	unsigned int point_count          = 0;
	unsigned short combo_timer        = 0;
	unsigned short coin_value         = 50;
	unsigned short combo_text_value;

	unsigned short rock_timer         = 0;
	unsigned short rock_cooldown      = 65;

	bool particle_spawn_spacing       = false;

	void spawn_spacedust();
	void spawn_explosion(Vector2 pos);
	void spawn_rock();
	void spawn_projectile();
	void spawn_coin(Rock rock); // TODO: try implementing entity pool

	void remove_dead_entities();  // TODO: make these into one function

	void media_init();
	void level_init();

	void update();
	void render();
};