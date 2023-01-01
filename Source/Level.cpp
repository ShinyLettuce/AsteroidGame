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
	point_count = 0;

	for (Coin& c : all_coins)
	{
		c.dead = true;
	}
	for (Rock& r : all_rocks)
	{
		r.dead = true;
	}

	remove_dead_entities();
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
	new_coin.position.x = rock.position.x + (float)GetRandomValue(-60,60);
	new_coin.position.y = rock.position.y + (float)GetRandomValue(-60, 60);
	all_coins.push_back(new_coin);
}

void Level::remove_dead_entities()
{
	all_rocks.remove_if([](const Rock& r) -> bool {return r.dead; });
	all_coins.remove_if([](const Coin& c) -> bool {return c.dead; });
}

//  #--------#
//  | UPDATE |
//  #--------#

void Level::update()
{
	rock_timer++;

	if (rock_timer >= rock_spawnrate(point_count,rock_cooldown) && mario.dead == false)
	{
		spawn_rock();
		rock_timer = 0;
	}

	if (mario.shot_fired == true)
	{
		spawn_projectile();
		mario.shot_fired = false;
	}

	for (Rock &r : all_rocks)
	{
		// rock hits edge
		if (r.position.x > 450 || r.position.x < 0 || r.position.y > 450)
		{
			r.dead = true;
		}
		
		// shot hits rock
		if (r.position.x <= shot.position.x + shot.size &&
			r.position.x + r.size >= shot.position.x &&
			r.position.y + r.size >= shot.position.y &&
			r.position.y <= shot.position.y + shot.size)
		{
			r.dead = true;
			for (int i = 0; i < GetRandomValue(4, 8); i++)
			{
			spawn_coin(r);
			}
		}
		
		// rock hits player
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
		// coin hits edge
		if (c.position.x > 450 || c.position.x < 0 || c.position.y > 450)
		{
			c.dead = true;
		}

		// coin hits player
		if (c.position.x <= mario.position.x + mario.size &&
			c.position.x + c.size >= mario.position.x &&
			c.position.y + c.size >= mario.position.y &&
			c.position.y <= mario.position.y + mario.size &&
			mario.dead == false)
		{
			c.dead = true;

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
	
	mario.update();
	shot.update();

	remove_dead_entities();
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

	if (combo_timer > 0)
	{
	DrawText(TextFormat("%03i", combo_text_value), mario.position.x + 35, mario.position.y, 16, YELLOW); //draw combo text
	}
	DrawText(TextFormat("%05i",point_count), 195, 10, 24, BLUE);
}
