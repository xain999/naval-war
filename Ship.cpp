#include "Ship.h"


Ship::Ship(void)								//default constructor
{
	DeltaMove = 0 ;
	score = 0 ;
}


Ship::~Ship(void)								//destructor
{
}


float Ship::getMove()
{
	return DeltaMove ;
}


void Ship::ChangePosition()			//changing position of ship
{
	if (BottomLeft.X < -7.0f + pos.X)
		pos.X -= 0.1f ;

	else if (BottomLeft.X > -7.0f + pos.X)
		pos.X += 0.1f ;
}


void Ship::Fire()			//firing bomb
{
	bombs.BombFired(angle , power) ;
}


bool Ship::CheckBomb(int scene, int player)
{
	if (bombs.CheckBlast(scene))
	{
		bombs.initializeBomb();
		return 1;
	}

	return 0 ;
}


void Ship::DEC2STR(int x, char *a)
{
	char temp[3] ;

	for (int i = 0 ; i < 3 ; i++)
	{
		temp[i] = x % 10 + '0' ;
		x = x / 10 ;
	}

	for (int i = 0 ; i < 3 ; i++)
		*(a + i) = temp[2-i] ;

	a[3] = '\0' ;
}


void Ship::SaveToFile()	//saving highscore to file
{
	ofstream out ;
	ifstream in ;
	int HScore[6] = {0,0,0} ;
	in.open(fileName, ios::binary);

	
	for (int i = 0 ; i < 3 || in.eof() ; i++)		//reading previously saved data
	{
		in.read(reinterpret_cast<char *> (HScore + i) , sizeof(int));

		if (HScore[i] < 0)
			HScore[i] = 0 ;
	}

	in.close();

	for (int i = 0 ; i < 3 ; i++)	//comparing High Score
	{
		if (score > HScore[i])
		{
			for (int j = 0 ; j < 3 ; j++)
				HScore[i+j+1] = HScore[i+j] ;

			HScore[i] = score ;
			break ;
		}
	}

	out.open(fileName, ios::binary);

	for (int i = 0 ; i < 3 ; i++)		//writing updated data saved data
		out.write(reinterpret_cast<char *> (HScore + i) , sizeof(int));

	out.close();
}


point Ship::getPosition()	//current position of the ship
{

	return CurrentPosition;
}


void Ship::calculateScore(point position)	//calculate the total score of the bomb
{
	float temp = bombs.calc_Score(position) ;

	if (temp <= 3.0)
		score += 100 ;

	else if (3.0 < temp && temp <= 5.0)
		score += 75 ;

	else if (5.0 < temp && temp <= 6.5)
		score += 50 ;

	else if (6.5 < temp && temp <= 8.0)
		score += 25 ;
}


int Ship::getScore()
{
	return score ;
}


point Ship::getBombPosition()
{
	return bombs.nxtPos ;
}