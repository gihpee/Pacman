#pragma once
#include <SFML/Graphics.hpp>
#include <String>
#include <fstream>

class UIPanel
{
	sf::Font font;
	sf::Text text;
	int highscore;
	std::ifstream inputFile;
	std::ofstream outputFile;

public:
	UIPanel()
	{
		font.loadFromFile("C:/Users/gihpe/OneDrive/Рабочий стол/учеба/Pacman_Morychev/Pacman/data/Font.ttf");
		text = sf::Text("", font, 20);
		text.setPosition(10, 10);
		inputFile = std::ifstream("C:/Users/gihpe/OneDrive/Рабочий стол/учеба/Pacman_Morychev/Pacman/data/highscore.txt");
		inputFile >> highscore;
		inputFile.close();
	}
	int score = 0;
	void update() 
	{	
		if (score > highscore)
		{
			outputFile = std::ofstream("C:/Users/gihpe/OneDrive/Рабочий стол/учеба/Pacman_Morychev/Pacman/data/highscore.txt");
			outputFile << score;
			outputFile.close();
			std::string str = "SCORE:" + std::to_string(score) + "                                                  HIGHSCORE:" + std::to_string(score);
			text.setString(str);
		}
		else
		{
			std::string str = "SCORE:" + std::to_string(score) + "                                                  HIGHSCORE:" + std::to_string(highscore);
			text.setString(str);

		}
	};
	void render(sf::RenderWindow& window) 
	{
		window.draw(text);
	};
};