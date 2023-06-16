#include "Pacman.h"
#include <SFML/Graphics.hpp>


Pacman::Pacman(int xPos, int yPos)
{
    direction = Direction::NONE;
    shape.setRadius(PACKMAN_RADIUS);
    shape.setFillColor(PACKMAN_COLOR);
    shape.setPosition(sf::Vector2f(xPos, yPos));
}

void Pacman::updatePacmanDirection() {
    direction = Direction::NONE;
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

void Pacman::update(float elapsedTime, std::vector<sf::FloatRect> fields, std::vector<Entity*>& objects, std::vector<Ghost*>& ghosts)
{
    const float step = PACKMAN_SPEED * elapsedTime;

    Pacman::updatePacmanDirection();

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

    for (int i = 0; i < objects.size(); i++)
        if (moveRect(pacmanBounds, movement).intersects(objects[i]->getBounds())) {
            if (objects[i]->isSuper())
            {
                for (int j = 0; j < ghosts.size(); j++) {
                    if (!ghosts[j]->state->eaten())
                    {
                        delete ghosts[j]->state;
                        ghosts[j]->state = new Frightened();
                        ghosts[j]->state->timerFrightenedMode();
                    }
                }
            }
            delete objects[i];
            objects.erase(objects.begin() + i);
        }

    for (int i = 0; i < ghosts.size(); i++)
    {
        if (moveRect(pacmanBounds, movement).intersects(ghosts[i]->getBounds()))
        {
            if (ghosts[i]->state->superPacGumEaten())
            {
                delete ghosts[i]->state;
                ghosts[i]->state = new Eaten();
            }
            //иначе - конец игры
        }
    }

    shape.move(movement);

}

sf::Vector2f Pacman::getPos()
{
    return shape.getPosition();
}