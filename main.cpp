#include <SFML/Graphics.hpp>
#include "game.h"

void handleEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        // ������ �������� ����
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void update(sf::Clock& clock, Game& game)
{
    const float elapsedTime = clock.getElapsedTime().asSeconds();
    clock.restart();
    game.updateGame(elapsedTime);
}

void render(sf::RenderWindow& window, const Game& game)
{
    window.clear();
    game.render(window);
    window.display();
}



int main()
{
    sf::RenderWindow window(sf::VideoMode(836, 836), "PacMan by gihpee", sf::Style::Close);
    sf::Clock clock;

    Game game;

    while (window.isOpen())
    {
        handleEvents(window);
        update(clock, game);
        render(window, game);

        if (!game.getState())
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                game = *new Game;
            }
        }
    }

    return 0;
}