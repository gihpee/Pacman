#include "Ghost.h"
#include "Pacman.h"
#include <time.h>


void Ghost::update(float elapsedTime, Pacman* pacman, std::vector<sf::FloatRect> fields)
{
	sf::Vector2f movement(0.f, 0.f);

	float step = 100.f * elapsedTime;

	if (this->state->insideHouse() && (!this->state->eaten()))
	{	
		//HOUSE MODE
		if (shape.getPosition().x != 9 * 44 + 6 && shape.getPosition().y > 10 * 44 + 6)
		{
			if (this->strategy->name == 'B' || this->strategy->name == 'I')
			{
				movement.x += 2.f;
			}
			else
			{
				movement.x -= 2.f;
			}
		}
		if (shape.getPosition().x == 9 * 44 + 6 && shape.getPosition().y > 10 * 44 + 6)
			movement.y -= 2.f;
		if (shape.getPosition().y == 10 * 44 + 6)
		{
			if (this->strategy->name == 'B')
			{
				if (shape.getPosition().x != 6 * 44 + 6)
				{
					movement.x -= 2.f;
				}
				else
				{
					delete this->state;
					state = new Chase();
				}
			}
			if (this->strategy->name == 'I')
			{
				if (shape.getPosition().x != 8 * 44 + 6)
				{
					movement.x -= 2.f;
				}
				else
				{
					delete this->state;
					state = new Chase();
				}
			}
			if (this->strategy->name == 'P')
			{
				if (shape.getPosition().x != 10 * 44 + 6)
				{
					movement.x += 2.f;
				}
				else
				{
					delete this->state;
					state = new Chase();
				}
			}
			if (this->strategy->name == 'C')
			{
				if (shape.getPosition().x != 12 * 44 + 6)
				{
					movement.x += 2.f;
				}
				else
				{
					delete this->state;
					state = new Chase();
				}
			}
		}
		
	}
	else if (this->state->insideHouse() && this->state->eaten())
	{	
		//EATEN
		//shape.setFillColor(sf::Color(190, 190, 190));
		texture.loadFromFile("C:/Users/gihpe/OneDrive/������� ����/�����/Pacman_Morychev/Pacman/data/Dead.png");
		shape.setTexture(&texture);
	}
	else if (this->state->superPacGumEaten())
	{	
		clock_t end = clock();
		if (((double)(end - this->state->timer) / CLOCKS_PER_SEC) > 10.0)
		{
			delete this->state;
			state = new Chase();
		}
		else
		{	
			//FRIGHTENED MODE
			float step = 100.f * elapsedTime;
			int rand_num = 1 + rand() % 4;

			if (rand_num == 1)
			{	
				direction = Direction::RIGHT;
				movement.x += step;
			}
			else if (rand_num == 2)
			{	
				direction = Direction::LEFT;
				movement.x -= step;
			}
			else if (rand_num == 3)
			{	
				direction = Direction::DOWN;
				movement.y += step;
			}
			else
			{	
				direction = Direction::UP;
				movement.y -= step;
			}

		}
	}
	else if (this->state->isScatter())
	{
		clock_t end = clock();
		if (((double)(end - this->state->timer) / CLOCKS_PER_SEC) > 10.0)
		{
			delete this->state;
			state = new Chase();

			sf::Vector2f vec = strategy->getMovement_chase(this, pacman);
			movement.x += vec.x * step;
			movement.y += vec.y * step;
		}
		else
		{
			//SCATTER MODE
			sf::Vector2f vec = strategy->getMovement_scatter(this);
			movement.x += vec.x * step;
			movement.y += vec.y * step;
		}
	}
	else
	{
		clock_t end = clock();
		if (((double)(end - this->state->timer) / CLOCKS_PER_SEC) > 10.0)
		{
			delete this->state;
			state = new Scatter();

			sf::Vector2f vec = strategy->getMovement_scatter(this);
			movement.x += vec.x * step;
			movement.y += vec.y * step;
		}
		else
		{
			sf::Vector2f vec = strategy->getMovement_chase(this, pacman);
			movement.x += vec.x * step;
			movement.y += vec.y * step;
		}
	}
	//movement = strategy->getMovement();


	const sf::FloatRect ghostBounds = shape.getGlobalBounds();

	if (movement.y > 0)
	{
		direction = Direction::DOWN;
	}
	else if (movement.y < 0)
	{
		direction = Direction::UP;
	}
	else if (movement.x < 0)
	{
		direction = Direction::LEFT;
	}
	else if (movement.x > 0)
	{
		direction = Direction::RIGHT;
	}

	for (int i = 0; i < fields.size(); i++)
		if (moveRect(ghostBounds, movement).intersects(fields[i])) {
			switch (direction)
			{
			case Direction::UP:
				movement.y += step;
				break;
			case Direction::DOWN:
				movement.y -= step;
				break;
			case Direction::LEFT:
				movement.x += step;
				break;
			case Direction::RIGHT:
				movement.x -= step;
				break;
			case Direction::NONE:
				break;
			}
		}

	this->shape.move(movement);
}

sf::Vector2f Ghost::getPos()
{
	return shape.getPosition();
}

Blinky::Blinky(int x, int y)
{
	shape.setPosition(sf::Vector2f(x, y));
	shape.setRadius(16.f);
	//shape.setFillColor(sf::Color(255, 0, 0));
	texture.loadFromFile("C:/Users/gihpe/OneDrive/������� ����/�����/Pacman_Morychev/Pacman/data/Blinky.png");
	shape.setTexture(&texture);
	strategy = new BlinkyS();
	this->state = new House();
}

Clyde::Clyde(int x, int y)
{
	shape.setPosition(sf::Vector2f(x, y));
	shape.setRadius(16.f);
	//shape.setFillColor(sf::Color(255, 150, 0));
	texture.loadFromFile("C:/Users/gihpe/OneDrive/������� ����/�����/Pacman_Morychev/Pacman/data/Clyde.png");
	shape.setTexture(&texture);
	strategy = new ClydeS();
	this->state = new House();
}

Inky::Inky(int x, int y)
{
	shape.setPosition(sf::Vector2f(x, y));
	shape.setRadius(16.f);
	//shape.setFillColor(sf::Color(0, 0, 255));
	texture.loadFromFile("C:/Users/gihpe/OneDrive/������� ����/�����/Pacman_Morychev/Pacman/data/Inky.png");
	shape.setTexture(&texture);
	strategy = new InkyS();
	this->state = new House();
}

Pinky::Pinky(int x, int y) 
{
	shape.setPosition(sf::Vector2f(x, y));
	shape.setRadius(16.f);
	//shape.setFillColor(sf::Color(0, 160, 100));
	texture.loadFromFile("C:/Users/gihpe/OneDrive/������� ����/�����/Pacman_Morychev/Pacman/data/Pinky.png");
	shape.setTexture(&texture);
	strategy = new PinkyS();
	this->state = new House();
}