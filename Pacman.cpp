#include "Pacman.h"
#include <SFML/Graphics.hpp>


Pacman::Pacman(int xPos, int yPos)
{
    direction = Direction::NONE;
    shape.setRadius(PACKMAN_RADIUS);
    shape.setFillColor(PACKMAN_COLOR);
    texture.loadFromFile("C:/Users/gihpe/OneDrive/������� ����/�����/Pacman_Morychev/Pacman/data/Pacman_right.png");
    shape.setTexture(&texture);
    shape.setPosition(sf::Vector2f(xPos, yPos));
}

void Pacman::updatePacmanDirection() {
    direction = Direction::NONE;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        direction = Direction::UP;
        texture.loadFromFile("C:/Users/gihpe/OneDrive/������� ����/�����/Pacman_Morychev/Pacman/data/Pacman_up.png");
        shape.setTexture(&texture);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        direction = Direction::DOWN;
        texture.loadFromFile("C:/Users/gihpe/OneDrive/������� ����/�����/Pacman_Morychev/Pacman/data/Pacman_down.png");
        shape.setTexture(&texture);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        direction = Direction::LEFT;
        texture.loadFromFile("C:/Users/gihpe/OneDrive/������� ����/�����/Pacman_Morychev/Pacman/data/Pacman_left.png");
        shape.setTexture(&texture);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        direction = Direction::RIGHT;
        texture.loadFromFile("C:/Users/gihpe/OneDrive/������� ����/�����/Pacman_Morychev/Pacman/data/Pacman_right.png");
        shape.setTexture(&texture);
    }
}

void Pacman::update(float elapsedTime, std::vector<sf::FloatRect> fields, std::vector<Entity*>& objects, std::vector<Ghost*>& ghosts, UIPanel* &panel, GameState* &gstate)
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
                panel->score += 100;
            }
            else
            {
                panel->score += 10;
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
                panel->score += 500;
            }
            //����� - ����� ����
            else
            {
                if (!ghosts[i]->state->eaten())
                {
                    delete gstate;
                    gstate = new GameOverState();
                }
            }
        }
    }

    shape.move(movement);

    if (shape.getPosition().x < 0)
    {
        shape.setPosition(800 - abs(shape.getPosition().x), shape.getPosition().y);
    }
    else if (shape.getPosition().x > 800)
    {
        shape.setPosition(abs(800 - shape.getPosition().x), shape.getPosition().y);
    }

}

sf::Vector2f Pacman::getPos()
{
    return shape.getPosition();
}