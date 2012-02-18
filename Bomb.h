#pragma once
#include "point.h"
class Bomb		//class bomb
{
protected:
	static const float DEG2RAD;		//ration of degree to radian
	static const float gravity;		//acceleration due to gravity
	static float radius ;			//radius of the bomb

	point currentPos ;				//current position of the Bomb
	point nxtPos ;					//Next Position of the Bomb
	point start ;					//start position of the bomb
	point color ;					//color of the bomb

	float time;						//time of flight

	friend class AlliedShip ;		//making friend class AlliedShip
	friend class SovietShip ;		//making friend class SovietShip
	friend class Ship ;				//make friend class Ship

	void DrawBomb();				//drawing bomb
	
public:
	//constructor and destructor
	Bomb(void);
	virtual ~Bomb(void);

	//member functions
	void BombFired(float, float);			//firing bomb
	bool CheckBlast(int);		//Checking whether the bomb will blast or not
	void initializeBomb() ;			//initializing the bomb
	float calc_Score(point);			//calculate the score

};

