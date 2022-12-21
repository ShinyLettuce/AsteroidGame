#include "Entity.h"

#include <cmath>
#include <iostream>

void Player::update()
{
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

    // normalizing of movement

    float length = sqrt(input.x * input.x + input.y * input.y);
    if (length > FLT_EPSILON)
    {
        input.x /= length;
        input.y /= length;
    }

    position.x += input.x * speed.x;
    position.y += input.y * speed.y;

    input = { 0,0 };

    // PLAYER CHARGED SHOT

    shot_fired = false;

    if (IsKeyDown(KEY_Z))
    {
        charge_time++;
        std::cout << charge_time << std::endl;
        color = YELLOW;
        if (charge_time >= 60)
        {
            color = RED;
        }
    }
    if (IsKeyReleased(KEY_Z))
    {
        if (charge_time >= 60)
        {
            std::cout << "shot fired" << std::endl;
            shot_fired = true;
        }
        else
        {
            std::cout << "not enough charge" << std::endl;
        }
        color = WHITE;
        charge_time = 0;
    }
}

void Player::render()
{
    DrawRectangle((int)position.x, (int)position.y, 20, 20, color);
    return;
}

void Rock::update()
{
    if (dead == true)
    {
        return;
    }
    
    if (position.x > 450 || position.x < 0)
    {
        dead = true;
    }
    if (position.y > 450)
    {
        dead = true;
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

    DrawRectangle((int)position.x, (int)position.y, size, size, color);
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

    DrawRectangle((int)position.x, (int)position.y, 10, 10, WHITE);
    return;
}