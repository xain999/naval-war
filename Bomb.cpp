#include "Bomb.h"

const float Bomb::DEG2RAD = 3.14159/180 ;
const float Bomb::gravity = -9.81 ;
float Bomb::radius = .5 ;


Bomb::Bomb(void)
{
	time = 0 ;

	color.X = 1.0 ;
	color.Y = 1.0 ;
	color.Z = 1.0 ;
}


Bomb::~Bomb(void)
{
}


void Bomb::BombFired(float angle, float power)
{

	this->nxtPos.X = start.X + time * cos(angle * DEG2RAD) ;
	this->nxtPos.Y = start.Y + ( power / 30 ) * sin(angle * DEG2RAD) * time + ( gravity * time * time ) / 1000 ;

	glColor3f(color.X, color.Y, color.Z) ;
	this->DrawBomb() ;

	currentPos = nxtPos ;
	time += 0.4 ;
}

 
void Bomb::DrawBomb()
{
   glBegin(GL_TRIANGLE_FAN);
 
   for (int i=0; i < 360; i++)
   {
      float degInRad = i*DEG2RAD;
	  glVertex3f(cos(degInRad)*radius + currentPos.X , sin(degInRad)*radius + currentPos.Y , -99.9);
   }
 
   glEnd();
}


bool Bomb::CheckBlast(int environment)	//checking whether to blast the bomb or not
{
	if (environment == 0)	//for jungle
	{
		if ( ((-35 * nxtPos.X) + (15 * nxtPos.Y) <= 825) && (nxtPos.Y <= 25) && ((40 * nxtPos.X) + (15 * nxtPos.Y) <= 975) )
			return 1;

	}

	else if (environment == 1)	//for city
	{
		if ( ((30 * nxtPos.X) + (-22 * nxtPos.Y) >= -990) && (nxtPos.Y <= 30) && ((22 * nxtPos.X) + (22.5 * nxtPos.Y) <= 917) && (nxtPos.X >= -31 && nxtPos.X <= 33.5) )
			return 1;

	}


	if (nxtPos.Y <= -15)
	{
		return 1 ;
	}

	return 0 ;
}


void Bomb::initializeBomb()
{
	time = 0 ;
}


float Bomb::calc_Score(point position)	//calculate the score of he bomb
{
	float temp;

	temp = ( (position.X - nxtPos.X) * (position.X - nxtPos.X) ) + ( (position.Y - nxtPos.Y) * (position.Y - nxtPos.Y) ) ;

	temp = sqrt(temp) ;
	return temp ;
}