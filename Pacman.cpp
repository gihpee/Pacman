#include "Pacman.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


Pacman::Pacman(int xPos, int yPos)
{
    direction = Direction::NONE;
    shape.setRadius(PACKMAN_RADIUS);
    shape.setFillColor(PACKMAN_COLOR);
    texture.loadFromFile("C:/Users/gihpe/OneDrive/Рабочий стол/учеба/Pacman_Morychev/Pacman/data/Pacman_right.png");
    shape.setTexture(&texture);
    shape.setPosition(sf::Vector2f(xPos, yPos));

    gumBuffer.loadFromFile("C:/Users/gihpe/OneDrive/Рабочий стол/учеба/Pacman_Morychev/Pacman/data/gum.wav");
    gum = sf::Sound(gumBuffer);

    startBuffer.loadFromFile("C:/Users/gihpe/OneDrive/Рабочий стол/учеба/Pacman_Morychev/Pacman/data/start.wav");
    start = sf::Sound(startBuffer);
    start.play();

    superGumBuffer.loadFromFile("C:/Users/gihpe/OneDrive/Рабочий стол/учеба/Pacman_Morychev/Pacman/data/superGum.wav");
    superGum = sf::Sound(superGumBuffer);

    killBuffer.loadFromFile("C:/Users/gihpe/OneDrive/Рабочий стол/учеба/Pacman_Morychev/Pacman/data/kill.wav");
    kill = sf::Sound(killBuffer);

    winBuffer.loadFromFile("C:/Users/gihpe/OneDrive/Рабочий стол/учеба/Pacman_Morychev/Pacman/data/win.wav");
    win = sf::Sound(winBuffer);

    deathBuffer.loadFromFile("C:/Users/gihpe/OneDrive/Рабочий стол/учеба/Pacman_Morychev/Pacman/data/death.wav");
    death = sf::Sound(deathBuffer);
}

void Pacman::updatePacmanDirection() {
    direction = Direction::NONE;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        direction = Direction::UP;
        texture.loadFromFile("C:/Users/gihpe/OneDrive/Рабочий стол/учеба/Pacman_Morychev/Pacman/data/Pacman_up.png");
        shape.setTexture(&texture);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        direction = Direction::DOWN;
        texture.loadFromFile("C:/Users/gihpe/OneDrive/Рабочий стол/учеба/Pacman_Morychev/Pacman/data/Pacman_down.png");
        shape.setTexture(&texture);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        direction = Direction::LEFT;
        texture.loadFromFile("C:/Users/gihpe/OneDrive/Рабочий стол/учеба/Pacman_Morychev/Pacman/data/Pacman_left.png");
        shape.setTexture(&texture);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
        || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        direction = Direction::RIGHT;
        texture.loadFromFile("C:/Users/gihpe/OneDrive/Рабочий стол/учеба/Pacman_Morychev/Pacman/data/Pacman_right.png");
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
                superGum.play();
            }
            else
            {
                panel->score += 10;
                gum.play();
            }
            delete objects[i];
            objects.erase(objects.begin() + i);
        }

    if (objects.size() == 0)
    {
        //выигрыш
        win.play();
        delete gstate;
        gstate = new WinState();
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
                kill.play();
            }
            //иначе - конец игры
            else
            {
                if (!ghosts[i]->state->eaten())
                {   
                    death.play();
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