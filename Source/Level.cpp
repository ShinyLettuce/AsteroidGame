#include "Level.h"

//  #------------#
//  | INITIALISE |
//  #------------#

void Level::level_init()
{
	mario.position      = { 220,355 };
	mario.speed         = { 5,5 };
	mario.charge_time   = 0;
	mario.charging_shot = false;
	mario.dead          = false;
	mario.color         = WHITE;
	point_count         = 0;

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

//  #---------------#
//  |SPAWN FUNCTIONS|  (PLUS REMOVE DEAD FUNCTIONS)
//  #---------------#

void Level::spawn_spacedust()
{
		Particle dust;
		dust.position  = { random_float_in_range(20.f,430.f),0 };
		dust.speed     = { 0,random_float_in_range(3,10) };
		dust.direction = { 0,1 };
		dust.color     = LIGHTGRAY;

		all_particles.push_back(dust);
}

void Level::spawn_explosion(Vector2 pos)
{
	for (int i = 0; i < 50; i++)
	{
		Particle fire;
		fire.explosion = true;
		fire.position  = pos;
		fire.speed     = { random_float_in_range(4,6),random_float_in_range(4,6) };
		fire.direction = normalize(cosf(random_float_in_range(0,2 * PI)),sinf(random_float_in_range(0,2 * PI)));
		//normalize(fire.direction.x, fire.direction.y);

		fire.color = RED;
		if (i > 4)
		{
			fire.color = YELLOW;
		}
		if (i > 8)
		{
			fire.color = ORANGE;
		}

		all_particles.push_back(fire);

	}
		screen_flash_timer = 10;
}

void Level::spawn_charge_particles()
{
	Particle charge;
	charge.charge    = true;
	charge.position  = { random_float_in_range(mario.position.x - 30,mario.position.x + 50),random_float_in_range(mario.position.y - 30,mario.position.y + 50) };
	charge.direction = normalize(mario.position.x + 10 - charge.position.x, mario.position.y + 10 - charge.position.y);
	charge.speed     = { random_float_in_range(3,5),random_float_in_range(3,5) };
	charge.size      = 4;
	charge.color     = SKYBLUE;
	//normalize(charge.direction.x, charge.direction.y);

	all_particles.push_back(charge);
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
	// PLAYER
	mario.update();

	//PARTICLES
	spawn_spacedust();
	if (mario.charging_shot == true && mario.dead == false)
	{
		spawn_charge_particles();
	}
	for (Particle &p : all_particles)
	{
		if (p.position.x > 450 || p.position.x < 0 || p.position.y > 450 || p.position.y < 0)
		{
			p.dead = true;
		}
		if (p.charge == true)
		{
			p.direction = normalize(mario.position.x + 10 - p.position.x, mario.position.y + 10 - p.position.y);
			//normalize(p.direction.x, p.direction.y);

			if (collision(p.position, mario.position, p.size, mario.size) || mario.shot_fired == true)
			{
				p.dead = true;
			}
		}
		p.update();
	}

	// PROJECTILE
	if (mario.shot_fired == true)
	{
		spawn_projectile();
		PlaySoundMulti(Media::laser);
		mario.shot_fired = false;
	}
	shot.update();

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
			PlaySoundMulti(Media::death);
		}
		if (collision(r.position,mario.position,r.size,mario.size) &&
			mario.dead == false)
		{
			mario.dead = true;
			combo_timer = 0;
			spawn_explosion(mario.position);
			PlaySoundMulti(Media::death);
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
			PlaySoundMulti(Media::collectible);

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

	// SCREEN FLASH
	if (screen_flash_timer > 7)
	{
		background = BLUE;
	}
	else if (screen_flash_timer > 5)
	{
		background = WHITE;
	}
	else if (screen_flash_timer > 3)
	{
		background = RED;
	}
	else
	{
		background = BLACK;
	}
	
	if (screen_flash_timer > 0)
	{
	screen_flash_timer--;
	}

	remove_dead_entities();
}

//  #--------#
//  | RENDER |
//  #--------#

void Level::render()
{
	ClearBackground(background);

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
	DrawText(TextFormat("+" "%i",combo_text_value), (int)mario.position.x + 35, (int)mario.position.y, 16, YELLOW);
	}
	DrawText(TextFormat("%02i",point_count), 210, 10, 24, BLUE);
}
