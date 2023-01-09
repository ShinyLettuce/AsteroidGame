#pragma once
#include "raylib.h"
#include "Math.h"

class Entity
{
public:
    Vector2 position = {};
    Vector2 speed = {};
    Color color;
    int size;
    bool dead = false;

    virtual void update()
    {
    }

    virtual void render()
    {
    }

    virtual void kill()
    {
    }
};

class Player : public Entity
{
public:
    Vector2 position = { 225,225 };
    Vector2 speed = { 4.5,4.5 };
    int size = 20;
    bool dead = true;
    Vector2 input = { 0,0 };
    Color color = WHITE;

    //Texture2D ship = LoadTexture("Ship2.png");

    int charge_time = 0;
    bool shot_fired = false;

    void update();
    void render();
};

class Rock : public Entity
{
public:
    Vector2 position = { random_float_in_range(20.f,430.f),0};
    Vector2 speed = { 4,4 };
    int size = 20;
    Vector2 direction = random_direction();
    Color color = ORANGE;

    void update();
    void render();
};

class Projectile : public Entity
{
public:
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
    //Vector2 direction = {};
    Color color = RED;

    void update();
    void render();

};

class Particle : public Entity
{
public:
    Vector2 position = {};
    Vector2 speed = {};

    bool explosion = false;

    void update();
    void render();
};