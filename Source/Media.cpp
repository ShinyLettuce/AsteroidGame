#include "Media.h"

Sound Media::menusound;
Sound Media::collectible;
Sound Media::laser;
Sound Media::death;

Texture2D Media::ship;
Texture2D Media::rock;
Texture2D Media::shot;

 void Media::media_init()
{
	InitAudioDevice();

	menusound   = LoadSound("menu.wav");
	collectible = LoadSound("collectible.wav");
	laser       = LoadSound("laser2.0.wav");
	death       = LoadSound("death.wav");

	ship = LoadTexture("Ship3.1.png");
	rock = LoadTexture("Rock2.0.png");
	shot = LoadTexture("shot.png");
}
