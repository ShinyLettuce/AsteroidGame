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
    float length = sqrt(input.x * input.x + input.y * input.y);
    if (length > FLT_EPSILON) // FLT_EPSILON because we want to avoid using zero
    {
        input.x /= length;
        input.y /= length;
    }

    position.x += input.x * speed.x;
    position.y += input.y * speed.y;

    input = { 0,0 };

    // PLAYER CHARGED SHOT

    if (IsKeyDown(KEY_Z))
    {
        charge_time++;
        //std::cout << charge_time << std::endl;
        color = YELLOW;
        speed = { 2,2 };
        if (charge_time >= 60)
        {
            color = RED;
        }
    }
    if (IsKeyReleased(KEY_Z))
    {
        if (charge_time >= 60)
        {
            //std::cout << "shot fired" << std::endl;
            shot_fired = true;
        }
        else
        {
            //std::cout << "not enough charge" << std::endl;
        }
        speed = { 4.5,4.5 };
        color = WHITE;
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

    DrawTexture(rock, (int)position.x, (int)position.y, WHITE);
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

    DrawRectangle((int)position.x, (int)position.y, size, size, WHITE);
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
    position.x += speed.x;
    position.y += speed.y;
}

void Particle::render()
{
    DrawRectangle((int)position.x, (int)position.y, 4, 4, color);
    return;
}