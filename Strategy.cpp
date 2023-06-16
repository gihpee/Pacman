#include "Strategy.h"

BlinkyS::BlinkyS() { this->name = 'B'; } 

sf::Vector2f BlinkyS::getMovement_scatter(Ghost* ghost)
{
	float x_g = ghost->getPos().x;
	float y_g = ghost->getPos().y;

	if (abs(25 * 32 - x_g) > abs(0 - y_g))
	{
		float cef = (25 * 32 - x_g) / abs(25 * 32 - x_g);
		return sf::Vector2f(cef, 0);
	}
	else
	{
		float cef = (0 - y_g) / abs(0 - y_g);
		return sf::Vector2f(0, cef);
	}
}

sf::Vector2f BlinkyS::getMovement_chase(Ghost* ghost, Pacman* pacman) 
{
	float x_p = pacman->getPos().x;
	float y_p = pacman->getPos().y;
	float x_g = ghost->getPos().x;
	float y_g = ghost->getPos().y;

	if (abs(x_p - x_g) > abs(y_p - y_g))
	{
		float cef = (x_p - x_g) / abs(x_p - x_g);
		return sf::Vector2f(cef, 0);
	}
	else
	{
		float cef = (y_p - y_g) / abs(y_p - y_g);
		return sf::Vector2f(0, cef);
	}
}

PinkyS::PinkyS() { this->name = 'P'; }

sf::Vector2f PinkyS::getMovement_scatter(Ghost* ghost)
{
	float x_g = ghost->getPos().x;
	float y_g = ghost->getPos().y;

	if (abs(0 - x_g) > abs(0 - y_g))
	{
		float cef = (0 - x_g) / abs(0 - x_g);
		return sf::Vector2f(cef, 0);
	}
	else
	{
		float cef = (0 - y_g) / abs(0 - y_g);
		return sf::Vector2f(0, cef);
	}
}

sf::Vector2f PinkyS::getMovement_chase(Ghost* ghost, Pacman* pacman) 
{
	float x_p = pacman->getPos().x + 2;
	float y_p = pacman->getPos().y + 2;
	float x_g = ghost->getPos().x;
	float y_g = ghost->getPos().y;

	if (abs(x_p - x_g) > abs(y_p - y_g))
	{
		float cef = (x_p - x_g) / abs(x_p - x_g);
		return sf::Vector2f(cef, 0);
	}
	else
	{
		float cef = (y_p - y_g) / abs(y_p - y_g);
		return sf::Vector2f(0, cef);
	}
}

ClydeS::ClydeS() { this->name = 'C'; }

sf::Vector2f ClydeS::getMovement_scatter(Ghost* ghost)
{
	float x_g = ghost->getPos().x;
	float y_g = ghost->getPos().y;

	if (abs(0 - x_g) > abs(25 * 32 - y_g))
	{
		float cef = (0 - x_g) / abs(0 - x_g);
		return sf::Vector2f(cef, 0);
	}
	else
	{
		float cef = (25 * 32 - y_g) / abs(25 * 32 - y_g);
		return sf::Vector2f(0, cef);
	}
}

sf::Vector2f ClydeS::getMovement_chase(Ghost* ghost, Pacman* pacman) 
{
	float x_p = pacman->getPos().x;
	float y_p = pacman->getPos().y;
	float x_g = ghost->getPos().x;
	float y_g = ghost->getPos().y;

	float dist = pow(pow(x_p - x_g, 2) + pow(y_p - y_g, 2), 0.5);

	if (dist <= 8 * 32)
	{
		if (abs(x_p - x_g) > abs(y_p - y_g))
		{
			float cef = (x_p - x_g) / abs(x_p - x_g);
			return sf::Vector2f(cef, 0);
		}
		else
		{
			float cef = (y_p - y_g) / abs(y_p - y_g);
			return sf::Vector2f(0, cef);
		}
	}
	else
	{
		return getMovement_scatter(ghost);
	}
}

InkyS::InkyS() { this->name = 'I'; }

sf::Vector2f InkyS::getMovement_scatter(Ghost* ghost)
{
	float x_g = ghost->getPos().x;
	float y_g = ghost->getPos().y;

	if (abs(25 * 32 - x_g) > abs(25 * 32 - y_g))
	{
		float cef = (25 * 32 - x_g) / abs(25 * 32 - x_g);
		return sf::Vector2f(cef, 0);
	}
	else
	{
		float cef = (25 * 32 - y_g) / abs(25 * 32 - y_g);
		return sf::Vector2f(0, cef);
	}
}

sf::Vector2f InkyS::getMovement_chase(Ghost* ghost, Pacman* pacman)
{
	float x_p = pacman->getPos().x + 2;
	float y_p = pacman->getPos().y + 2;
	float x_g = ghost->getPos().x;
	float y_g = ghost->getPos().y;

	if (abs(x_p - x_g) > abs(y_p - y_g))
	{
		float cef = (x_p - x_g) / abs(x_p - x_g);
		return sf::Vector2f(cef, 0);
	}
	else
	{
		float cef = (y_p - y_g) / abs(y_p - y_g);
		return sf::Vector2f(0, cef);
	}
}