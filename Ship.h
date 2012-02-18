#pragma once
#include "point.h"
#include "glut.h"
#include "Bomb.h"

class Ship :									//class ship inheriting class point
	public point
{
protected:
	float DeltaMove ;							//can ship moves towards right
	int power ;									//power of the bomb
	int angle ;									//angle of the bomb
	int score ;									//score of the player
	point pos ;									//adjusting the ship
	point turret ;								//turret start position
	point CurrentPosition;						//current position of the ship
	Bomb bombs ;								//Array of bombs
	string fileName ;							//name to the file

public:

	//Taking points to keep track of the coordinates of Ship
	point TopLeft ;									
	point TopRight ;
	point BottomLeft ;
	point BottomRight ;

	Ship(void);
	virtual ~Ship(void);

	float getMove() ;								//checking moves left to move Left
	void ChangePosition() ;							//changing ships coordinates
	void Fire();									//fire bomb
	bool CheckBomb(int, int);						//Check the bomb
	void DEC2STR(int ,char *);						//changing a decimal to string
	void SaveToFile();								//Save HighScore to File
	point getPosition();							//geet the position of the ship
	void calculateScore(point);						//calculate the score of the player
	int getScore();									//return score
	point getBombPosition();						//get bombs position


	virtual void intialize() = 0;					//intialize the ships
	virtual void DisplayHighScore() = 0 ;			//Display High Score
	virtual void display_Atr() = 0 ;				//display score angle and power
	virtual bool checkLeft() = 0 ;					//checking whether to move left or not
	virtual bool checkRight() = 0 ;					//checking whether to move right or not
	virtual void draw(void) = 0 ;					//virtual drawing fuction
	virtual void move(char) = 0 ;					//virtual move fuction
	virtual void changePower(char) = 0 ;			//increasing or decreasing power
	virtual void changeAngle(char) = 0 ;			//increasing or decreasing angle
};

