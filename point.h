#pragma once
#include <iostream>
#include "glut.h"
#include <cmath>
#include <fstream>
#include <string>

using namespace std ;


class point						//base class point
{
	friend class AlliedShip ;
	friend class SovietShip ;
	friend class Ship ;
	friend class Bomb ;

protected:
	float X ;					//X coordinate
	float Y ;					//Y coordinate
	float Z ;					//Z coordinate

public:
	point(void);
	point(float , float , float) ;
	virtual ~point(void);

	point operator+(const point&);
	point operator-(const point&);
	point operator*(const float&);
	point operator/(const float&);

	float getX();
	float getY();
};