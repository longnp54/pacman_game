﻿#include <cmath>
#include <SFML/Graphics.hpp>

#include "Headers/Global.hpp"
#include "Headers/Pacman.hpp"
#include "Headers/MapCollision.hpp"
#include <algorithm>


Pacman::Pacman() :
	animation_over(0),
	dead(0),
	direction(0),
	energizer_timer(0)
	//position={0, 0}

{
		position.x=0;
		position.y=0;
}

bool Pacman::get_animation_over()
{
	return animation_over;
}

bool Pacman::get_dead()
{
	return dead;
}

unsigned char Pacman::get_direction()
{
	return direction;
}

unsigned short Pacman::get_energizer_timer()
{
	return energizer_timer;
}

void Pacman::draw(bool i_victory, sf::RenderWindow& i_window)
{
	unsigned char frame = static_cast<unsigned char>(floor(animation_timer / static_cast<float>(PACMAN_ANIMATION_SPEED)));

	sf::Sprite sprite;

	sf::Texture texture;

	sprite.setPosition(position.x, position.y);

	if (1 == dead || 1 == i_victory)
	{
		if (animation_timer < PACMAN_DEATH_FRAMES * PACMAN_ANIMATION_SPEED)
		{
			animation_timer++;

			texture.loadFromFile("Images/PacmanDeath" + std::to_string(CELL_SIZE) + ".png");

			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(CELL_SIZE * frame, 0, CELL_SIZE, CELL_SIZE));

			i_window.draw(sprite);
		}
		else
		{
			//You can only die once.
			animation_over = 1;
		}
	}
	else
	{
		texture.loadFromFile("Images/Pacman" + std::to_string(CELL_SIZE) + ".png");

		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(CELL_SIZE * frame, CELL_SIZE * direction, CELL_SIZE, CELL_SIZE));

		i_window.draw(sprite);

		animation_timer = (1 + animation_timer) % (PACMAN_ANIMATION_FRAMES * PACMAN_ANIMATION_SPEED);
	}
}

void Pacman::reset()
{
	animation_over = 0;
	dead = 0;

	direction = 0;

	animation_timer = 0;
	energizer_timer = 0;
}

void Pacman::set_animation_timer(unsigned short i_animation_timer)
{
	animation_timer = i_animation_timer;
}

void Pacman::set_dead(bool i_dead)
{
	dead = i_dead;

	if (1 == dead)
	{
		//Making sure that the animation starts from the beginning.
		animation_timer = 0;
	}
}

void Pacman::set_position(short i_x, short i_y)
{
	//position = {i_x, i_y};
	position.x=i_x;
	position.y=i_y;
}
void Pacman::update(unsigned char i_level,  std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map)

{

    bool walls[4] = {};

    walls[0] = map_collision(0, 0, PACMAN_SPEED + position.x, position.y, i_map);

    walls[1] = map_collision(0, 0, position.x, position.y - PACMAN_SPEED, i_map);

    walls[2] = map_collision(0, 0, position.x - PACMAN_SPEED, position.y, i_map);

    walls[3] = map_collision(0, 0, position.x, PACMAN_SPEED + position.y, i_map);



    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))

    {

        if (!walls[0]) // Không thể rẽ nếu có tường

        {

            direction = 0;

        }

    }



    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))

    {

        if (!walls[1])

        {

            direction = 1;

        }

    }



    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))

    {

        if (!walls[2])

        {

            direction = 2;

        }

    }



    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))

    {

        if (!walls[3])

        {

            direction = 3;

        }

    }



    if (!walls[direction])

    {

        switch (direction)

        {

            case 0: position.x += PACMAN_SPEED; break;

            case 1: position.y -= PACMAN_SPEED; break;

            case 2: position.x -= PACMAN_SPEED; break;

            case 3: position.y += PACMAN_SPEED; break;

        }

    }



    if (position.x < -CELL_SIZE)

    {

        position.x = CELL_SIZE * MAP_WIDTH - PACMAN_SPEED;

    }

    else if (position.x >= CELL_SIZE * MAP_WIDTH)

    {

        position.x = PACMAN_SPEED - CELL_SIZE;

    }



    if (map_collision(1, 0, position.x, position.y, i_map))

    {

        // Pacman ăn energizer

        energizer_timer = static_cast<unsigned short>(ENERGIZER_DURATION / pow(2, i_level));

    }

    else

    {

        energizer_timer = std::max(0, energizer_timer - 1);

    }


}

Position Pacman::get_position()
{
	return position;
}