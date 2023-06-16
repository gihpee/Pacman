#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Pacman.h"
#include "Entity.h"
#include "Ghost.h"
#include "Cell.h"
#include "UIPanel.h"
#include "GameState.h"

class Game
{
	int width;
	int height;
	std::vector<Entity*> objects;
	std::vector<Ghost*> ghosts;
	std::vector<Cell*> cells;
	Pacman* pacman;
	UIPanel* panel;
	GameState* gstate;


public:

	Game();
	std::vector<Entity> getEntities();
	std::vector<Cell> getCells();

	Pacman getPacman();
	bool getState();
	void updateGame(float elapsedTime); // изменения координат объектов
	void render(sf::RenderWindow& window) const; // отрисовка
	~Game() = default;

};

