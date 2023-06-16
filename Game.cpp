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
    const int height = 19;
    int width = 19;
    std::string Map[height] = {
    "0000000000000000000",
    "###################",
    "#     *  #  *     #",
    "# ## ### # ### ## #",
    "# ## ### # ### ## #",
    "#        *        #",
    "###  # ##### #  ###",
    "###  #   #   #  ###",
    "     ### # ###     ",
    "     #       #     ",
    "###  #   *   #  ###",
    "###    ##0##    ###",
    "#   # #bi0pc# #   #",
    "#   #  #####  #   #",
    "##               ##",
    "#* #   #####   # *#",
    "# ####   #   #### #",
    "#        *        #",
    "###################",
    };

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (Map[i][j] == '#')
                cells.push_back(new Cell(j * 44, i * 44, 44));
            else if (Map[i][j] == ' ')
                objects.push_back(new PacGum(j * 44 + 17, i * 44 + 17, 10));
            else if (Map[i][j] == '*')
                objects.push_back(new SuperPacGum(j * 44 + 16, i * 44 + 16, 12));
            else if (Map[i][j] == 'b')
                ghosts.push_back(new Blinky(j * 44 + 6, i * 44 + 6));
            else if (Map[i][j] == 'i')
                ghosts.push_back(new Inky(j * 44 + 6, i * 44 + 6));
            else if (Map[i][j] == 'p')
                ghosts.push_back(new Pinky(j * 44 + 6, i * 44 + 6));
            else if (Map[i][j] == 'c')
                ghosts.push_back(new Clyde(j * 44 + 6, i * 44 + 6));

    pacman = new Pacman(9*44 + 6, 14*44 + 6);
    panel = new UIPanel();
    gstate = new ActiveState();

}

void Game::updateGame(float elapsedTime) {
    if (gstate->state)
    {
        std::vector<sf::FloatRect> fields;

        std::vector<sf::FloatRect> gums;

        for (int i = 0; i < cells.size(); i++)
            fields.push_back(cells[i]->getBounds());

        for (int i = 0; i < ghosts.size(); i++)
            ghosts[i]->update(elapsedTime, pacman, fields);

        pacman->update(elapsedTime, fields, objects, ghosts, panel, gstate);

        panel->update();
    }
    else
    {
        gstate->update(elapsedTime);
    }
}


void Game::render(sf::RenderWindow& window) const {
    if (gstate->state)
    {
        for (int i = 0; i < cells.size(); i++)
            cells[i]->render(window);

        for (int i = 0; i < objects.size(); i++)
            objects[i]->render(window);

        for (int i = 0; i < ghosts.size(); i++)
            ghosts[i]->render(window);

        pacman->render(window);
        panel->render(window);
    }
    else
    {
        gstate->render(window);
    }
}



	

