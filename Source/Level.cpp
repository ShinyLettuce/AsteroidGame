#include "Level.h"
#include <iostream>

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

	for (Rock& r : all_rocks)
	{
		r.dead = true;
	}
	remove_dead_rocks();
}

//  #---------------#
//  |SPAWN FUNCTIONS|  (PLUS REMOVE DEAD FUNCTIONS)
//  #---------------#

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
	new_coin.position = rock.position;
	all_coins.push_back(new_coin);
}

void Level::remove_dead_rocks()
{
	all_rocks.remove_if([](const Rock& r) -> bool {return r.dead; });
}

void Level::remove_dead_coins()
{
	all_coins.remove_if([](const Coin& c) -> bool {return c.dead; });
}

//  #--------#
//  | UPDATE |
//  #--------#

void Level::update()
{
	rock_timer++;

	if (rock_timer >= 20 && mario.dead == false)
	{
		spawn_rock();
		rock_timer = 0;
	}

	if (mario.shot_fired == true)
	{
		spawn_projectile();
	}

	for (Rock &r : all_rocks)
	{
		if (r.position.x > 450 || r.position.x < 0)
		{
			r.dead = true;
		}
		if (r.position.y > 450)
		{
			r.dead = true;
		}
		
		if (r.position.x <= shot.position.x + shot.size &&
			r.position.x + r.size >= shot.position.x &&
			r.position.y + r.size >= shot.position.y &&
			r.position.y <= shot.position.y + shot.size)
		{
			r.dead = true;
			spawn_coin(r);
		}

		if (r.position.x <= mario.position.x + mario.size &&
			r.position.x + r.size >= mario.position.x &&
			r.position.y + r.size >= mario.position.y &&
			r.position.y <= mario.position.y + mario.size)
		{
			mario.dead = true;
		}

		r.update();
	}
	for (Coin& c : all_coins)
	{
		c.update();
	}
	
	mario.update();
	shot.update();


	remove_dead_rocks();
}

//  #--------#
//  | RENDER |
//  #--------#

void Level::render()
{
	ClearBackground(BLACK);

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

	DrawText("00",211,10,24,WHITE);
}
