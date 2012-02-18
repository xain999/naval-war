#pragma once
#include "ship.h"

class SovietShip :											//class Soviet Ship inheriting class Ship
	public Ship
{

public:
	SovietShip(void);
	virtual ~SovietShip(void);

	virtual void intialize();								//intialize the ships
	virtual bool checkLeft() ;								//whether to move left or not
	virtual bool checkRight() ;								//whether to move right or not
	virtual void draw(void) ;								//drawing fuction for class Soviet Ship
	virtual void move(char) ;								//virtual move fuction
	virtual void changePower(char) ;						//increasing or decreasing power
	virtual void changeAngle(char) ;						//increasing or decreasing angle
	virtual void display_Atr();								//display angle power and score
	virtual void DisplayHighScore();						//Display High Score
};

