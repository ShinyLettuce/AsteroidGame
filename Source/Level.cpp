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

void Level::update()
{
	
	mario.update();

	if (mario.shot_fired == true)
	{
		spawn_projectile();
		Rock new_rock;
		spawn_rock(new_rock);
	}

	shot.update();

	for (Rock &r : all_rocks)
	{
		r.update();
	}
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
