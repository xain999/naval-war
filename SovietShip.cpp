#include "SovietShip.h"
float DEG2RAD = 3.14159/180 ;


SovietShip::SovietShip(void)							//default constructor
{
	power = 0 ;
	angle = 90 ;

	pos.X = -56.0 ;
	pos.Y = -15.0 ;

	BottomLeft.X = -7.0f + pos.X ;						//lower left
	BottomLeft.Y = 0.0f + pos.Y ;

	TopLeft.X = -7.0f + pos.X ;							//upper left
	TopLeft.Y = 2.0f + pos.Y ;
				
	TopRight.X = +7.5f + pos.X ;						//upper right
	TopRight.Y =  3.0f + pos.Y ;
				
	BottomRight.X = 5.0f + pos.X ;						//lower right
	BottomRight.Y = 0.0f + pos.Y ;

	bombs.currentPos = TopRight ;						//assigning current position to bomb
	bombs.nxtPos = TopRight ;
	bombs.start = TopRight ;

	bombs.start.X -= 2 ;
	turret = bombs.start ;

	CurrentPosition = (BottomRight + BottomLeft) / 2 ;

	fileName = "soviet.DAT" ;
}


SovietShip::~SovietShip(void)								//destructor
{
}


void SovietShip::draw(void)									//virtual draw fuction
{
	

	glBegin(GL_QUADS); //1st red box coordinates
		glColor3f(1.0f, 0.0f, 0.0);
		glVertex3f(-7.0f + pos.X , 0.0f + pos.Y , -100.0f);
		glVertex3f(-7.0f + pos.X , 2.0f + pos.Y , -100.0f);
		glVertex3f(3.5f + pos.X , 2.0f + pos.Y , -100.0f);
		glVertex3f(2.0f + pos.X , 0.0f + pos.Y , -100.0f);
	glEnd();

	glBegin(GL_QUADS); //2nd black box coordinates
		glColor3f(0.0f, 0.0f, 0.0);
		glVertex3f(-7.0f + pos.X , 0.0f + pos.Y , -100.0f);
		glVertex3f(-7.0f + pos.X , 2.0f + pos.Y , -100.0f);
		glVertex3f(5.5f + pos.X , 2.9f + pos.Y , -100.0f);
		glVertex3f(3.5f + pos.X , 0.0f + pos.Y , -100.0f);
	glEnd();

	glBegin(GL_QUADS); //3rd red box coordinates
		glColor3f(1.0f, 0.0f, 0.0);
		glVertex3f(-7.0f + pos.X , 0.0f + pos.Y , -100.0f);
		glVertex3f(-7.0f + pos.X , 2.0f + pos.Y , -100.0f);
		glVertex3f(7.5f + pos.X , 3.0f + pos.Y , -100.0f);
		glVertex3f(5.0f + pos.X , 0.0f + pos.Y , -100.0f);
	glEnd();

	bombs.start.X = turret.X + (3 * cos(DEG2RAD*angle) ) ;
	bombs.start.Y = turret.Y + (3 * sin(DEG2RAD*angle) ) ;

	glBegin(GL_QUADS); //Turret coordinates
		glColor3f(1.0f, 0.5f, 0.0);
		glVertex3f(turret.X - 0.4, turret.Y, -100.0f);
		glVertex3f(bombs.start.X - 0.25, bombs.start.Y , -100.0f);
		glVertex3f(bombs.start.X + 0.25, bombs.start.Y , -100.0f);
		glVertex3f(turret.X + 0.4, turret.Y, -100.0f);
	glEnd();

	glBegin(GL_QUADS); //left black chimney
		glColor3f(0.0f, 0.0f, 0.0);
		glVertex3f(-4.5f + pos.X , 0.0f + pos.Y , -100.0f);
		glVertex3f(-4.5f + pos.X , 6.0f + pos.Y , -100.0f);
		glVertex3f(-3.5f + pos.X , 6.0f + pos.Y , -100.0f);
		glVertex3f(-3.5f + pos.X , 0.0f + pos.Y , -100.0f);
	glEnd();

	glBegin(GL_QUADS); //right black chimney
		glColor3f(0.0f, 0.0f, 0.0);
		glVertex3f(-3.3f + pos.X , 0.0f + pos.Y , -100.0f);
		glVertex3f(-3.3f + pos.X , 6.0f + pos.Y , -100.0f);
		glVertex3f(-2.3f + pos.X , 6.0f + pos.Y , -100.0f);
		glVertex3f(-2.3f + pos.X , 0.0f + pos.Y , -100.0f);
	glEnd();

	glBegin(GL_QUADS); //blue cabin windshield
		glColor3f(0.0f, 0.5f, 0.7f);
		glVertex3f(-0.3f + pos.X , 3.0f + pos.Y , -100.0f);
		glVertex3f(0.0f + pos.X , 3.6f + pos.Y , -100.0f);
		glVertex3f(4.5f + pos.X , 3.6f + pos.Y , -100.0f);
		glVertex3f(4.5f + pos.X , 3.0f + pos.Y , -100.0f);
	glEnd();

	glBegin(GL_QUADS); //red main cabin
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(-2.0f + pos.X , 0.0f + pos.Y , -100.0f);
		glVertex3f(-2.0f + pos.X , 4.0f + pos.Y , -100.0f);
		glVertex3f(4.5f + pos.X , 4.0f + pos.Y , -100.0f);
		glVertex3f(4.5f + pos.X , 0.0f + pos.Y , -100.0f);
	glEnd();


	//glBegin(GL_QUADS); //blue cabin windshield
	//	glColor3f(0.0f, 0.5f, 0.7f);
	//	glVertex3f(-0.3f + pos.X , 2.7f + pos.Y , -100.0f);
	//	glVertex3f(0.0f + pos.X , 3.3f + pos.Y , -100.0f);
	//	glVertex3f(4.05f + pos.X , 3.3f + pos.Y , -100.0f);
	//	glVertex3f(4.05f + pos.X , 2.7f + pos.Y , -100.0f);
	//glEnd();
}


void SovietShip::move(char a)								//Moving Ship
{
	if (DeltaMove >= -12 && a == 'a')								//checking left moves
	{
		BottomLeft.X -= 0.1 ;
		BottomRight.X -= 0.1 ;
		TopLeft.X -= 0.1 ;
		TopRight.X -= 0.1 ;
		bombs.start.X -= 0.1 ;
		turret.X -= 0.1 ;
		
		DeltaMove -= 0.1 ;
		CurrentPosition = (TopRight + TopLeft) / 2 ;

		return ;
	}

	
	
	else if (DeltaMove <= 12 && a == 'd')								//checking Right moves
	{
		BottomLeft.X += 0.1 ;
		BottomRight.X += 0.1 ;
		TopLeft.X += 0.1 ;
		TopRight.X += 0.1 ;
		bombs.start.X += 0.1 ;
		turret.X += 0.1 ;
		CurrentPosition = (TopRight + TopLeft) / 2 ;

		DeltaMove += 0.1 ;
	}
}



bool SovietShip::checkLeft()									//checking whether to move ship or not
{
	if ( BottomLeft.X == -7.0 + pos.X )
		return 0 ;

	return 1 ;
}


bool SovietShip::checkRight()									//checking whether to move ship or not
{
	if ( BottomLeft.X == -7.0 + pos.X )
		return 0 ;

	return 1 ;
}



void SovietShip::changePower(char a)			//increasing or decreasing power
{

	if ( a == 'w' && power < 100 )			
		power++ ;


	else if ( a == 's' && power > 0 )
		power-- ;
}


void SovietShip::changeAngle(char a)			//increasing or decreasing power
{

	if ( a == 'w' && angle < 90 )
		angle++ ;


	else if ( a == 's' && angle > 0 )
		angle-- ;
}



void SovietShip::display_Atr()		//displaying attributes on the screen
{
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex3f(-55, 30.5, -100);
	glVertex3f(-55, 40, -100);
	glVertex3f(-32, 40, -100);
	glVertex3f(-37, 30.5, -100);
	glEnd();

	char a[20] = "Angle = " ;
	char p[20] = "Power = " ;
	char s[20] = "Score = " ;

	DEC2STR(angle, a+8);
	DEC2STR(power, p+8);
	DEC2STR(score, s+8);

	glColor3f(1.0, 1.0, 0);
	glRasterPos3f(-52, 36.5,-99);

	for(char *c = a ; *c!='\0';c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);


	glColor3f(1.0, 0.0, 0.0);
	glRasterPos3f(-52.5, 34,-99);

	for(char *c = p ; *c!='\0';c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

	glColor3f(1.0, 1.0, 0);
	glRasterPos3f(-52, 31.5,-99);

	for(char *c = s ; *c!='\0';c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

}



void SovietShip::DisplayHighScore()			//displaying high score
{
	ifstream in ;
	int HScore[3] = {0,0,0} ;
	char Scr[4] ;
	in.open(fileName, ios::binary);

	for (int i = 0 ; i < 3 || in.eof() ; i++)		//reading previously saved data
	{
		in.read(reinterpret_cast<char *> (HScore + i) , sizeof(int));

		if (HScore[i] < 0)
			HScore[i] = 0 ;
	}

	in.close();

	glColor3f(1, 1, 1);

	DEC2STR (HScore[0] , Scr);
	glRasterPos3f(5, -18 ,-99);

	//displaying power on screen
	for(char *c = Scr ; *c!='\0';c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	

	DEC2STR (HScore[1] , Scr);
	glRasterPos3f(5, -25,-99);

	//displaying power on screen
	for(char *c = Scr ; *c!='\0';c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);


	DEC2STR (HScore[2] , Scr);
	glRasterPos3f(5, -32,-99);

	//displaying power on screen
	for(char *c = Scr ; *c!='\0';c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
}


void SovietShip::intialize(void)							//default constructor
{
	power = 0 ;
	angle = 90 ;

	pos.X = -56.0 ;
	pos.Y = -15.0 ;

	BottomLeft.X = -7.0f + pos.X ;						//lower left
	BottomLeft.Y = 0.0f + pos.Y ;

	TopLeft.X = -7.0f + pos.X ;							//upper left
	TopLeft.Y = 2.0f + pos.Y ;
				
	TopRight.X = +7.5f + pos.X ;						//upper right
	TopRight.Y =  3.0f + pos.Y ;
				
	BottomRight.X = 5.0f + pos.X ;						//lower right
	BottomRight.Y = 0.0f + pos.Y ;

	bombs.currentPos = TopRight ;						//assigning current position to bomb
	bombs.nxtPos = TopRight ;
	bombs.start = TopRight ;

	bombs.start.X -= 2 ;
	turret = bombs.start ;

	CurrentPosition = (BottomRight + BottomLeft) / 2 ;

	score = 0 ;
	DeltaMove = 0 ;

}