#include "Entity.h"
#include "Level.h"
#include <cmath>
//#include <iostream>

void Player::update()
{
    if (dead == true)
    {
        return;
    }

    // PLAYER MOVEMENT

    if (IsKeyDown(KEY_UP))
    {
        input.y = -1;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        input.y = 1;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        input.x = -1;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        input.x = 1;
    }

    // normalizing input vector             TODO: put in math.cpp
    normalize(input.x, input.y);

    if ((position.x + input.x * speed.x) < 450 - size && (position.x + input.x * speed.x) > 0)
    {
        position.x += input.x * speed.x;
    }
    if ((position.y + input.y * speed.y) < 450 - size && (position.y + input.y * speed.y) > 0)
    {
        position.y += input.y * speed.y;
    }

    input = { 0,0 };

    // PLAYER CHARGED SHOT

    if (IsKeyDown(KEY_Z))
    {
        charging_shot = true;
        charge_time++;
        speed = { 2,2 };
        if (charge_time >= 60)
        {
            color = BLUE;
        }
    }
    if (IsKeyReleased(KEY_Z))
    {
        if (charge_time >= 60)
        {
            shot_fired = true;
        }
        speed = { 4.5,4.5 };
        color = WHITE;
        charging_shot = false;
        charge_time = 0;
    }
}

void Player::render()
{
    if (dead == true)
    {
        return;
    }

    DrawTexture(ship,(int)position.x,(int)position.y, color);
    //DrawRectangle((int)position.x, (int)position.y, size, size, color);
    return;
}

void Rock::update()
{
    if (dead == true)
    {
        return;
    }

    position.y += direction.y * speed.y;
    position.x += direction.x * speed.x;
    return;
}

void Rock::render()
{
    if (dead == true)
    {
        return;
    }

    DrawTexture(rock, (int)position.x, (int)position.y, color);
    //DrawRectangle((int)position.x, (int)position.y, size, size, color);
    return;
}

void Projectile::update()
{
    if (dead == true)
    {
        return;
    }

    position.y += speed.y;
    return;
}

void Projectile::render()
{
    if (dead == true)
    {
        return;
    }

    DrawTexture(shot, (int)position.x, (int)position.y, WHITE);
    //DrawRectangle((int)position.x, (int)position.y, size, size, WHITE);
    return;
}

void Coin::update()
{
    if (dead == true)
    {
        return;
    }

    position.y += speed.y;
    return;
}

void Coin::render()
{
    if (dead == true)
    {
        return;
    }

    DrawRectangle((int)position.x, (int)position.y, size, size, color);
    return;
}

void Particle::update()
{
    position.x += direction.x * speed.x;
    position.y += direction.y * speed.y;
}

void Particle::render()
{
    DrawRectangle((int)position.x, (int)position.y, size, size, color);
    return;
}