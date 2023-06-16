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
		if (shape.getPosition().x != 12 * 32 + 4 && shape.getPosition().y > 7 * 32 + 4)
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
		if (shape.getPosition().x == 12 * 32 + 4 && shape.getPosition().y > 7 * 32 + 4)
			movement.y -= 2.f;
		if (shape.getPosition().y == 7 * 32 + 4)
		{
			if (this->strategy->name == 'B')
			{
				if (shape.getPosition().x != 7 * 32 + 4)
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
				if (shape.getPosition().x != 9 * 32 + 4)
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
				if (shape.getPosition().x != 15 * 32 + 4)
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
				if (shape.getPosition().x != 17 * 32 + 4)
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
		shape.setFillColor(sf::Color(190, 190, 190));
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
			float step = 500.f * elapsedTime;
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

	for (int i = 0; i < fields.size(); i++)
		if (moveRect(ghostBounds, movement).intersects(fields[i])) {
			if (direction == Direction::DOWN || movement.y > 0)
			{
				movement.y -= 2;
			}
			else if (direction == Direction::UP || movement.y < 0)
			{
				movement.y += 2;
			}
			else if (direction == Direction::LEFT || movement.x < 0)
			{
				movement.x += 2;
			}
			else if (direction == Direction::RIGHT || movement.x > 0)
			{
				movement.x -= 2;
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
	shape.setRadius(12.f);
	shape.setFillColor(sf::Color(255, 0, 0));
	strategy = new BlinkyS();
	this->state = new House();
}

Clyde::Clyde(int x, int y)
{
	shape.setPosition(sf::Vector2f(x, y));
	shape.setRadius(12.f);
	shape.setFillColor(sf::Color(255, 150, 0));
	strategy = new ClydeS();
	this->state = new House();
}

Inky::Inky(int x, int y)
{
	shape.setPosition(sf::Vector2f(x, y));
	shape.setRadius(12.f);
	shape.setFillColor(sf::Color(0, 0, 255));
	strategy = new InkyS();
	this->state = new House();
}

Pinky::Pinky(int x, int y) 
{
	shape.setPosition(sf::Vector2f(x, y));
	shape.setRadius(12.f);
	shape.setFillColor(sf::Color(0, 160, 100));
	strategy = new PinkyS();
	this->state = new House();
}