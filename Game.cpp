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
    const int height = 25;
    int width = 25;
    std::string Map[height] = {
    "0000000000000000000000000",
    "#########################",
    "#  ## ###   #   ### ##  #",
    "#           #           #",
    "#  ##       *       ##  #",
    "#     #    ###    #     #",
    "###   ##    #    ##   ###",
    "00#   #           #   #00",
    "###      ###r###      ###",
    "         #bi0pc#         ",
    "      #  #######  #      ",
    "###   #     *     #   ###",
    "00#   #   #####   #   #00",
    "###   #     #     #   ###",
    "#           #           #",
    "#* ##  ###     ###  ## *#",
    "#   #      ###      #   #",
    "#   #       #       #   #",
    "#           #           #",
    "##     #    *    #     ##",
    "##     #   ###   #     ##",
    "##     #    #    #     ##",
    "# * #####   #   ##### * #",
    "#                       #",
    "#########################"
    };

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (Map[i][j] == '#')
                cells.push_back(new Cell(j * 32, i * 32, 32));
            else if (Map[i][j] == ' ')
                objects.push_back(new PacGum(j * 32 + 12, i * 32 + 12, 8));
            else if (Map[i][j] == '*')
                objects.push_back(new SuperPacGum(j * 32 + 11, i * 32 + 11, 10));
            else if (Map[i][j] == 'b')
                ghosts.push_back(new Blinky(j * 32 + 4, i * 32 + 4));
            else if (Map[i][j] == 'i')
                ghosts.push_back(new Inky(j * 32 + 4, i * 32 + 4));
            else if (Map[i][j] == 'p')
                ghosts.push_back(new Pinky(j * 32 + 4, i * 32 + 4));
            else if (Map[i][j] == 'c')
                ghosts.push_back(new Clyde(j * 32 + 4, i * 32 + 4));

    pacman = new Pacman(12*32 + 4, 15*32 + 4);
}

void Game::updateGame(float elapsedTime) {
    std::vector<sf::FloatRect> fields;

    std::vector<sf::FloatRect> gums;

    for (int i = 0; i < cells.size(); i++)
        fields.push_back(cells[i]->getBounds());

    for (int i = 0; i < ghosts.size(); i++)
        ghosts[i]->update(elapsedTime, pacman, fields);

    pacman->update(elapsedTime, fields, objects, ghosts);
}


void Game::render(sf::RenderWindow& window) const {
    for (int i = 0; i < cells.size(); i++)
        cells[i]->render(window);

    for (int i = 0; i < objects.size(); i++)
        objects[i]->render(window);

    for (int i = 0; i < ghosts.size(); i++)
        ghosts[i]->render(window);

    pacman->render(window);
}



	

