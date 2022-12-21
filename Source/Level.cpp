#include "Level.h"
#include <iostream>

void Level::spawn_projectile()
{
	shot.dead = false;
	shot.position = mario.position;
}

void Level::spawn_rock(const Rock& rock)
{
	all_rocks.push_back(rock);
}

void Level::remove_dead_rocks()
{
	all_rocks.remove_if([](const Rock& r) -> bool {return r.dead; });
}

void Level::update()
{
	rock_timer++;

	if (rock_timer >= 20)
	{

		Rock new_rock;
		spawn_rock(new_rock);
		rock_timer = 0;
	}

	mario.update();

	if (mario.shot_fired == true)
	{
		spawn_projectile();
	}

	shot.update();

	for (Rock &r : all_rocks)
	{
		r.update();
	}

	remove_dead_rocks();
}

void Level::render()
{
	ClearBackground(BLACK);

	mario.render();
	shot.render();

	for (Rock &r : all_rocks)
	{
		r.render();
	}
}
