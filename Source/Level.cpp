#include "Level.h"
//#include <iostream>

//  #------------#
//  | INITIALISE |
//  #------------#

void Level::level_init()
{
	mario.position = { 220,355 };
	mario.speed = { 5,5 };
	mario.charge_time = 0;
	mario.dead = false;
	mario.color = WHITE;
	point_count = 0;

	for (Coin& c : all_coins)
	{
		c.dead = true;
	}
	for (Rock& r : all_rocks)
	{
		r.dead = true;
	}
	for (Particle& p : all_particles)
	{
		if (p.explosion == true)
		{
			p.dead = true;
		}
	}
	remove_dead_entities();
}

void Level::media_init()
{
	InitAudioDevice();

	menusound = LoadSound("menu.wav");
	death = LoadSound("death.wav");
	collectible = LoadSound("collectible.wav");
}

//  #---------------#
//  |SPAWN FUNCTIONS|  (PLUS REMOVE DEAD FUNCTIONS)
//  #---------------#

void Level::spawn_spacedust()
{
	if (particle_spawn_spacing == false)
	{
		Particle dust;
		dust.position = { 225.f,-95.f };
		dust.speed = { random_float_in_range(-6,6),5.5f };
		dust.color = LIGHTGRAY;
		all_particles.push_back(dust);
		particle_spawn_spacing = true;
	}
	else
	{
		particle_spawn_spacing = false;
	}
}

void Level::spawn_explosion(Vector2 pos)
{
	for (int i = 0; i < 10; i++)
	{
		Particle fire;
		fire.explosion = true;
		fire.position = pos;
		fire.color = RED;
		fire.speed = { random_float_in_range(-5,5),random_float_in_range(-5,5) };
		all_particles.push_back(fire);
	}
}

void Level::spawn_projectile()
{
	shot.dead = false;
	shot.position.x = mario.position.x + 4;
	shot.position.y = mario.position.y;
}

void Level::spawn_rock()
{
	Rock rock;
	all_rocks.push_back(rock);
}

void Level::spawn_coin(Rock rock)
{
	Coin new_coin;
	new_coin.position.x = rock.position.x + (float)GetRandomValue(-60,60);
	new_coin.position.y = rock.position.y + (float)GetRandomValue(-60, 60);
	all_coins.push_back(new_coin);
}

void Level::remove_dead_entities()
{
	all_rocks.remove_if([](const Rock& r) -> bool {return r.dead; });
	all_coins.remove_if([](const Coin& c) -> bool {return c.dead; });
	all_particles.remove_if([](const Particle& p) -> bool {return p.dead; });
}

//  #--------#
//  | UPDATE |
//  #--------#

void Level::update()
{
	//PARTICLES
	spawn_spacedust();
	for (Particle &p : all_particles)
	{
		if (p.position.x > 450 || p.position.x < 0 || p.position.y > 450)
		{
			p.dead = true;
		}
		p.update();
	}

	//ROCKS
	rock_timer++;
	if (rock_timer >= rock_spawnrate(point_count,rock_cooldown) &&
		mario.dead == false)
	{
		spawn_rock();
		rock_timer = 0;
	}
	for (Rock &r : all_rocks)
	{
		if (r.position.x > 450 || r.position.x < 0 || r.position.y > 450)
		{
			r.dead = true;
		}
		if (collision(r.position,shot.position,r.size,shot.size))
		{
			r.dead = true;
			for (int i = 0; i < GetRandomValue(4, 8); i++)
			{
			spawn_coin(r);
			}
			spawn_explosion(r.position);
			PlaySoundMulti(death);
		}
		if (collision(r.position,mario.position,r.size,mario.size) &&
			mario.dead == false)
		{
			mario.dead = true;
			combo_timer = 0;
			spawn_explosion(mario.position);
			PlaySoundMulti(death);
		}
		r.update();
	}
	// COINS
	for (Coin& c : all_coins)
	{
		if (c.position.x > 450 || c.position.x < 0 || c.position.y > 450)
		{
			c.dead = true;
		}
		if (collision(c.position,mario.position,c.size,mario.size) &&
			mario.dead == false)
		{
			c.dead = true;
			PlaySoundMulti(collectible);

			combo_timer = 60;           // start/prolong combo (thinking of implementing combo as an entity)
			point_count += coin_value;
			combo_text_value = coin_value;
			coin_value += 10;
		}
		c.update();
	}
	if (combo_timer > 0)                // decrease combo timer
	{
		combo_timer--;
	}
	else                                // end combo
	{
		coin_value = 50;
	}

	
	if (mario.shot_fired == true)
	{
		spawn_projectile();
		mario.shot_fired = false;
	}
	shot.update();
	mario.update();

	remove_dead_entities();
}

//  #--------#
//  | RENDER |
//  #--------#

void Level::render()
{
	ClearBackground(BLACK);

	for (Particle p : all_particles)
	{
		if(p.position.y > 16)
		p.render();
	}
	mario.render();
	shot.render();
	for (Coin& c : all_coins)
	{
		c.render();
	}
	for (Rock &r : all_rocks)
	{
		r.render();
	}

	if (combo_timer > 0)
	{
	DrawText(TextFormat("+" "%i",combo_text_value), (int)mario.position.x + 35, (int)mario.position.y, 16, YELLOW); //draw combo text
	}
	DrawText(TextFormat("%02i",point_count), 210, 10, 24, BLUE);
}
