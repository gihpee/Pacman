#pragma once
#include <vector>
#include "Ghost.h"
#include "UIPanel.h"
#include "GameState.h"
//#include "Entity.h"

class Ghost;

static const sf::Color PACKMAN_COLOR = sf::Color(255, 216, 0);
static const float PACKMAN_SPEED = 120.f; // pixels per second.
static const float PACKMAN_RADIUS = 16.f; // pixels

class Pacman: public MovingEntity
{
public:
	Pacman(int xPos, int yPos);

	void updatePacmanDirection();

	void update(float elapsedTime, std::vector<sf::FloatRect> fields, std::vector<Entity*>& objects, std::vector<Ghost*>& ghosts, UIPanel* &panel, GameState* &gstate);

	sf::Vector2f getPos();

};

