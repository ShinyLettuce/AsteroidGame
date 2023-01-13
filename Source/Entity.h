#pragma once
#include "Media.h"
#include "Math.h"

class Entity
{
public:
    Vector2 position = {};
    Vector2 speed = {};
    Color color = WHITE;
    int size;
    bool dead = false;

    virtual void update()
    {
    }

    virtual void render()
    {
    }
};

class Player : public Entity
{
public:
    Texture2D ship = LoadTexture("Ship3.1.png");
    int size = 20;
    bool dead = true;
    Vector2 input = { 0,0 };

    int charge_time = 0;
    bool charging_shot = false;
    bool shot_fired = false;

    void update();
    void render();
};

class Rock : public Entity
{
public:
    Texture2D rock = LoadTexture("Rock2.0.png"); // this sucks since every new rock will load the texture      TODO: create asset manager (probably using pointers)
    Vector2 position = { random_float_in_range(20.f,430.f),0};
    Vector2 speed = { 6,6 };
    Vector2 direction = random_direction();
    int size = 20;

    void update();
    void render();
};

class Projectile : public Entity
{
public:
    Texture2D shot = LoadTexture("shot.png");
    Vector2 speed = { 0,-8 };
    int size = 12;
    bool dead = true;

    void update();
    void render();
};

class Coin : public Entity
{
public:
    Vector2 speed = {1.5,1.5};
    int size = 8;
    Color color = RED;

    void update();
    void render();

};

class Particle : public Entity
{
public:
    Vector2 position = {};
    Vector2 speed = {};
    Vector2 direction = {};
    int size = 2;

    bool explosion = false;
    bool charge = false;

    void update();
    void render();
};