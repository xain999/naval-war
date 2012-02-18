#pragma once
#include "ship.h"

class AlliedShip :									//class Allied Ship inheriting class Ship
	public Ship
{

public:
	AlliedShip(void);
	virtual ~AlliedShip(void);

	virtual void intialize();						//intialize the ships
	virtual bool checkLeft() ;						//whether to move left or not
	virtual bool checkRight() ;						//whether to move right or not
	virtual void draw(void) ;						//drawing fuction for class Allied Ship
	virtual void move(char) ;						//virtual move fuction
	virtual void changePower(char) ;				//increasing or decreasing power
	virtual void changeAngle(char) ;				//increasing or decreasing angle
	virtual void display_Atr();						//display angle power and score
	virtual void DisplayHighScore();				//Display High Score
};

