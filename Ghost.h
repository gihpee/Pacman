#pragma once
#include "State.h"
#include "Strategy.h"
#include "Entity.h"
#include "Pacman.h"

class Pacman;
class Strategy;

class Ghost : public MovingEntity
{
protected:
	sf::Color color;
	float radius = 12.f;

public:
	Ghost() {};
	Strategy* strategy;
	State* state;

	void update(float elapsedTime, Pacman* pacman, std::vector<sf::FloatRect> fields);
	sf::Vector2f getPos();

};

class Blinky : public Ghost 
{
public:
	Blinky(int x, int y);

};

class Clyde : public Ghost 
{
public:
	Clyde(int x, int y);
	
};

class Inky : public Ghost 
{
public:
	Inky(int x, int y);
	
};

class Pinky : public Ghost 
{
public:
	Pinky(int x, int y);
	
};