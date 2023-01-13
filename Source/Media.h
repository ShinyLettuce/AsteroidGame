#pragma once
#include "raylib.h"
 
struct Media
{
	static Sound menusound;
	static Sound collectible;
	static Sound laser;
	static Sound death;


	static Texture2D ship;
	static Texture2D rock;
	static Texture2D shot;

	static void media_init();
};
