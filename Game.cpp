#include "Game.h"
#include <string>
#include <vector>


Game::Game() {
    // create factory AbstractGhostFactory* ghostFactory;
    // read the text file with maze and positions of entities
    //if x - create wall and add into walls
    //if P - create pacman, add into objects
    //if b/p/i/c - create factories
    //create ghosts and add them into objects and ghosts
    //if . - create PacGum into objects
    //if o - create SuperPacGum
    //if - - create GhostHouse 
    const int height = 16;
    int width = 16;
    std::string Map[height] = {
    "################",
    "# # #  #  #  # #",
    "#          *   #",
    "# # # ### #  # #",
    "#   ## # ##    #",
    "##  # ### #   ##",
    "      # #   *   ",
    "##  # ### #   ##",
    "# * # ### #    #",
    "# # ## # ## #  #",
    "# #    *    #  #",
    "# # # ### # #  #",
    "##  #  #  #   ##",
    "# #### # ####  #",
    "# *    *       #",
    "################"
    };

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (Map[i][j] == '#')
                cells.push_back(new Cell(j * 50, i * 50, 50));
            else if (Map[i][j] == ' ')
                objects.push_back(new PacGum(j * 50 + 20, i * 50 + 20, 10));
            else if (Map[i][j] == '*')
                objects.push_back(new SuperPacGum(j * 50 + 15, i * 50 + 15, 20));

    pacman = new Pacman(60, 60);
}

void Game::updateGame(float elapsedTime) {
    std::vector<sf::FloatRect> fields;

    for (int i = 0; i < cells.size(); i++)
        fields.push_back(cells[i]->getBounds());

    pacman->update(elapsedTime, fields);
}


void Game::render(sf::RenderWindow& window) const {
    for (int i = 0; i < cells.size(); i++)
        cells[i]->render(window);

    for (int i = 0; i < objects.size(); i++)
        objects[i]->render(window);

    pacman->render(window);
}



	

