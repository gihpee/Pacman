#pragma once
#include <SFML/Graphics.hpp>
#include "Ghost.h"

class Ghost;
class Pacman;

class Strategy
{
public:
	char name;
	virtual sf::Vector2f getMovement_chase(Ghost* ghost, Pacman* pacman) = 0;
	virtual sf::Vector2f getMovement_scatter(Ghost* ghost) = 0;
};

class BlinkyS: public Strategy
{
public:
	BlinkyS();
	sf::Vector2f getMovement_scatter(Ghost* ghost) override;

	sf::Vector2f getMovement_chase(Ghost* ghost, Pacman* pacman) override;
};

class PinkyS : public Strategy
{
public:
	PinkyS();
	sf::Vector2f getMovement_scatter(Ghost* ghost) override;

	sf::Vector2f getMovement_chase(Ghost* ghost, Pacman* pacman) override;
};

class ClydeS : public Strategy
{
public:
	ClydeS();
	sf::Vector2f getMovement_scatter(Ghost* ghost) override;

	sf::Vector2f getMovement_chase(Ghost* ghost, Pacman* pacman) override;
};

class InkyS : public Strategy
{
public:
	InkyS();
	sf::Vector2f getMovement_scatter(Ghost* ghost) override;

	sf::Vector2f getMovement_chase(Ghost* ghost, Pacman* pacman) override;
};