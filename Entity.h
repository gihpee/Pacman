#pragma once
#include <SFML/Graphics.hpp>

enum struct Direction
{
	NONE,
	UP,
	DOWN,
	LEFT,
	RIGHT
};


class Entity
{
protected:
	int xPos;
	int yPos;
	int size;
	

public:
	virtual sf::FloatRect getBounds() = 0;
	//virtual void update() = 0;
	virtual void render(sf::RenderWindow& window) = 0;
};

class StaticEntity : public Entity {
protected:
	sf::FloatRect bounds;
	sf::RectangleShape shape;
public:
	sf::FloatRect getBounds() override {
		return shape.getGlobalBounds();
	}
};

class PacGum : public StaticEntity
{

public:
	PacGum(int x, int y, int s) {
		xPos = x;
		yPos = y;
		size = s;

	}
	void render(sf::RenderWindow& window) {
		shape.setFillColor(sf::Color(255, 183, 174));
		shape.setSize(sf::Vector2f(size, size));
		shape.setPosition(sf::Vector2f(xPos, yPos));
		window.draw(shape);
	}
};




class SuperPacGum : public StaticEntity
{
public:

	SuperPacGum(int x, int y, int s) {
		xPos = x;
		yPos = y;
		size = s;
	}
	void render(sf::RenderWindow& window) {
		shape.setFillColor(sf::Color(255, 0, 0));
		shape.setSize(sf::Vector2f(size, size));
		shape.setPosition(sf::Vector2f(xPos, yPos));
		window.draw(shape);
	}
};


class MovingEntity : public Entity {
protected:
	int speed;
	sf::Vector2i speedVec;
	Direction direction;
	sf::Texture texture;
	sf::CircleShape shape;

	//etc.

public:
	void unpdatePosition() {

	}
	void render(sf::RenderWindow& window) {
		window.draw(shape);
	}
	sf::FloatRect getBounds() {
		return shape.getGlobalBounds();
	}
	sf::FloatRect moveRect(sf::FloatRect rect1, sf::Vector2f movement) {
		rect1.left += movement.x;
		rect1.top += movement.y;
		return rect1;
	}
	//setters, getters, etc. 
};