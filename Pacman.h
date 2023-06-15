#pragma once
#include "Entity.h"
#include <vector>

static const sf::Color PACKMAN_COLOR = sf::Color(255, 216, 0);
static const float PACKMAN_SPEED = 120.f; // pixels per second.
static const float PACKMAN_RADIUS = 16.f; // pixels

class Pacman: public MovingEntity
{
public:
	Pacman(int xPos, int yPos) {
		direction = Direction::NONE;
        shape.setRadius(PACKMAN_RADIUS);
        shape.setFillColor(PACKMAN_COLOR);
        shape.setPosition(sf::Vector2f(xPos, yPos));

	}

	void updatePacmanDirection() {
        //direction = Direction::NONE;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
            || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            direction = Direction::UP;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
            || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            direction = Direction::DOWN;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
            || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            direction = Direction::LEFT;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
            || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            direction = Direction::RIGHT;
        }
	}

    void update(float elapsedTime, std::vector<sf::FloatRect> fields) {
        const float step = PACKMAN_SPEED * elapsedTime;

        updatePacmanDirection();

        sf::Vector2f movement(0.f, 0.f);
        switch (direction)
        {
        case Direction::UP:
            movement.y -= step;
            break;
        case Direction::DOWN:
            movement.y += step;
            break;
        case Direction::LEFT:
            movement.x -= step;
            break;
        case Direction::RIGHT:
            movement.x += step;
            break;
        case Direction::NONE:
            break;
        }

        const sf::FloatRect pacmanBounds = shape.getGlobalBounds();


        for (int i = 0; i < fields.size(); i++)
            if (moveRect(pacmanBounds, movement).intersects(fields[i])) {
                if (direction == Direction::DOWN)
                {
                    movement.y += -1;
                }
                else if (direction == Direction::UP)
                {
                    movement.y += 1;
                }
                else if (direction == Direction::LEFT)
                {
                    movement.x += 1;
                }
                else if (direction == Direction::RIGHT)
                {
                    movement.x += -1;
                }
            }

        shape.move(movement);


    }


};

