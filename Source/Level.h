#pragma once
#include "Entity.h"
#include "Math.h"
#include "Media.h"
#include <list>

class Level
{
	Projectile shot;
	std::list<Rock> all_rocks		  = {};
	std::list<Coin> all_coins         = {};
	std::list<Particle> all_particles = {};

	Color background = BLACK;

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
	void spawn_coin(Rock rock); 

	void remove_dead_entities();
public:
	Player mario;

	void level_init();

	void update();
	void render();
};