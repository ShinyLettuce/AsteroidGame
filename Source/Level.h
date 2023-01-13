#pragma once
#include "Entity.h"
#include "Math.h"
#include "Media.h"
#include <list>

class Level
{
public:
	Sound menusound;
	Sound death;
	Sound collectible;
	Sound laser;

	Player mario;
	Projectile shot;
	std::list<Rock> all_rocks		  = {};  // using list since that has the member function remove_if
	std::list<Coin> all_coins         = {};
	std::list<Particle> all_particles = {};

	Color background = BLACK;

	// Vector2 size;
	int point_count        = 0;
	int combo_timer        = 0;
	int coin_value         = 50;
	int combo_text_value   = 0;

	int rock_timer         = 0;
	int rock_cooldown      = 65;

	int screen_flash_timer = 0;

	void spawn_spacedust();
	void spawn_explosion(Vector2 pos);
	void spawn_charge_particles();
	void spawn_rock();
	void spawn_projectile();
	void spawn_coin(Rock rock); // TODO: try implementing entity pool

	void remove_dead_entities();  // TODO: make these into one function

	void media_init();
	void level_init();

	void update();
	void render();
};