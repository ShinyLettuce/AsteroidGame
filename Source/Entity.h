#pragma once
#include "raylib.h"
#include "Math.h"

class Entity
{
public:
    Vector2 position = {};
    Vector2 speed = {};
    Color color;
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
    Vector2 input = { 0,0 };
    Vector2 position = { 225,225 };
    Vector2 speed = { 4,4 };
    Color color = WHITE;
    int size = 15;

    int charge_time = 0;
    bool shot_fired = false;

    void update();
    void render();
};

class Rock : public Entity
{
public:
    Vector2 position = { random_float_in_range(20.f,430.f),0};
    Vector2 speed = { 2,2 };
    Vector2 direction = random_direction();
    Color color = BROWN;
    int size = 15;

    void update();
    void render();
};

class Projectile : public Entity
{
public:
    Vector2 speed = { 0,-7 };
    bool dead = true;

    void update();
    void render();
};