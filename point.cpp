#include "point.h"


point::point(void)								//default constructor
{
}


point::point(float x , float y , float z)		//overloaded constructor
{
	X = x ;
	Y = y ;
	Z = z ;
}


point::~point(void)								//destructor
{
}


point point::operator+(const point &a)	//overloading addition operator
{
	point temp;

	temp.X = X + a.X ;
	temp.Y = Y + a.Y ;
	temp.Z = Z + a.Z ;

	return temp ;
}


point point::operator-(const point &a)	//overloading subtraction operator
{
	point temp;

	temp.X = X - a.X ;
	temp.Y = Y - a.Y ;
	temp.Z = Z - a.Z ;

	return temp ;
}


point point::operator*(const float &a)	//overloading multiplication operator
{
	point temp;

	temp.X = X * a ;
	temp.Y = Y * a ;
	temp.Z = Z * a ;

	return temp ;
}


point point::operator/(const float &a)	//overloading division operator
{
	point temp;

	temp.X = X / a ;
	temp.Y = Y / a ;
	temp.Z = Z / a ;

	return temp ;
}


float point::getX()
{
	return X;
}



float point::getY()
{
	return Y;
}