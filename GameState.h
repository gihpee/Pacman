#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>

class GameState
{
protected:
	sf::RectangleShape shape;

	sf::Font font;
	sf::Text text;
	sf::Text text2;

	clock_t start;
	bool red;
	clock_t pres_enter;

public:
	bool state;
	virtual void update(float elapsedTime) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
};

class ActiveState : public GameState
{
public:
	ActiveState()
	{
		state = true;
	}
	void update(float elapsedTime) override {}
	void render(sf::RenderWindow& window) override {}
};

class WinState : public GameState
{
public:
	WinState()
	{
		start = clock();
		pres_enter = clock();
		shape.setFillColor(sf::Color(0, 0, 0));
		shape.setSize(sf::Vector2f(836, 836));
		shape.setPosition(sf::Vector2f(0, -836));

		font.loadFromFile("C:/Users/gihpe/OneDrive/Рабочий стол/учеба/Pacman_Morychev/Pacman/data/Font.ttf");
		text = sf::Text("YOU WON", font, 50);
		text.setPosition(300, -518);

		text2 = sf::Text("press Enter to continue", font, 30);
		text2.setPosition(200, -518);

		state = false;
		bool red = false;
	}
	void update(float elapsedTime) override
	{
		clock_t end = clock();

		if (((double)(end - start) / CLOCKS_PER_SEC) > 0.5)
		{
			switch (red)
			{
			case true:
				this->start = clock();
				red = false;
				text.setFillColor(sf::Color(255, 255, 255));
				break;
			case false:
				this->start = clock();
				red = true;
				text.setFillColor(sf::Color(0, 255, 0));
				break;
			}
		}

		if (((double)(end - pres_enter) / CLOCKS_PER_SEC) > 5.0)
		{
			text2.setPosition(250, 418);


		}

		if (shape.getPosition().y < 0)
		{
			shape.move(sf::Vector2f(0, 0.5));
		}

		if (text.getPosition().y < 318)
		{
			text.move(sf::Vector2f(0, 0.5));
		}
	}
	void render(sf::RenderWindow& window) override
	{
		window.draw(shape);
		window.draw(text);
		window.draw(text2);
	}
};

class GameOverState : public GameState
{
public:
	GameOverState()
	{	
		start = clock();
		pres_enter = clock();
		shape.setFillColor(sf::Color(0, 0, 0));
		shape.setSize(sf::Vector2f(836, 836));
		shape.setPosition(sf::Vector2f(0, -836));

		font.loadFromFile("C:/Users/gihpe/OneDrive/Рабочий стол/учеба/Pacman_Morychev/Pacman/data/Font.ttf");
		text = sf::Text("GAME OVER", font, 50);
		text.setPosition(300, -518);

		text2 = sf::Text("press Enter to continue", font, 30);
		text2.setPosition(200, -518);

		state = false;
		bool red = false;
	}
	void update(float elapsedTime) override
	{	
		clock_t end = clock();

		if (((double)(end - start) / CLOCKS_PER_SEC ) > 0.5)
		{	
			switch (red)
			{
			case true:
				this->start = clock();
				red = false;
				text.setFillColor(sf::Color(255, 255, 255));
				break;
			case false:
				this->start = clock();
				red = true;
				text.setFillColor(sf::Color(255, 0, 0));
				break;
			}
		}

		if (((double)(end - pres_enter) / CLOCKS_PER_SEC) > 5.0)
		{
			text2.setPosition(250, 418);

		}

		if (shape.getPosition().y < 0)
		{
			shape.move(sf::Vector2f(0, 0.5));
		}

		if (text.getPosition().y < 318)
		{
			text.move(sf::Vector2f(0, 0.5));
		}
	}
	void render(sf::RenderWindow& window) override
	{
		window.draw(shape);
		window.draw(text);
		window.draw(text2);
	}


};