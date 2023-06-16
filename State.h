#pragma once
#include <time.h>


class State
{
public:
	virtual bool superPacGumEaten() = 0;
	//virtual bool timerModeOver() = 0;
	virtual void timerFrightenedMode() = 0;
	virtual bool eaten() = 0;
	virtual bool outsideHouse() = 0;
	virtual bool insideHouse() = 0;
	clock_t timer;
	virtual bool isScatter() = 0;
	//virtual void computeNextDir() = 0;
	//virtual sf::Vector2f getTargetPosition(Pacman* pacman) = 0;

};

class House : public State
{
public:
	bool superPacGumEaten() override { return false; }
	bool eaten() override { return false; }
	bool outsideHouse() override { return false; }
	bool insideHouse() override { return true; }
	void timerFrightenedMode() override {};
	bool isScatter() override { return false; };
};

class Frightened : public State
{
public:
	bool superPacGumEaten() override { return true; }
	bool eaten() override { return false; }
	bool outsideHouse() override { return true; }
	bool insideHouse() override { return false; }
	void timerFrightenedMode() override {
		timer = clock();
	}
	bool isScatter() override { return false; };
};

class Eaten : public State
{
public:
	bool superPacGumEaten() override { return false; }
	bool eaten() override { return true; }
	bool outsideHouse() override { return false; }
	bool insideHouse() override { return true; }
	void timerFrightenedMode() {};
	bool isScatter() override { return false; };
};

class Chase : public State
{
public:
	bool superPacGumEaten() override { return false; }
	bool eaten() override { return false; }
	bool outsideHouse() override { return true; }
	bool insideHouse() override { return false; }
	void timerFrightenedMode() override {
		timer = clock();
	}
	bool isScatter() override { return false; };
};

class Scatter : public State
{
public:
	bool superPacGumEaten() override { return false; }
	bool eaten() override { return false; }
	bool outsideHouse() override { return true; }
	bool insideHouse() override { return false; }
	void timerFrightenedMode() override {
		timer = clock();
	}
	bool isScatter() override { return true; };
};