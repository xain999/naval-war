#include "AlliedShip.h"
float RAD = 3.14159/180 ;


AlliedShip::AlliedShip(void)						//default constructor
{
	power = 0 ;
	angle = 90 ;

	pos.X = +58.0 ;
	pos.Y = -15.0 ;

	BottomLeft.X = -7.0f + pos.X ;								//lower left
	BottomLeft.Y = 0.0f + pos.Y ;

	TopLeft.X = -8.5f + pos.X ;									//upper left
	TopLeft.Y = 3.0f + pos.Y ;
				
	TopRight.X = 8.5f + pos.X ;									//upper right
	TopRight.Y =  1.0f + pos.Y ;
				
	BottomRight.X = 7.0f + pos.X ;								//lower right
	BottomRight.Y = 0.0f + pos.Y ;

	bombs.currentPos = TopLeft ;						//assigning current position to bomb
	bombs.nxtPos = TopLeft ;
	bombs.start = TopLeft ;

	bombs.start.X += 2 ;
	turret = bombs.start ;
	turret.Y -= 0.1 ;

	CurrentPosition = (BottomRight + BottomLeft) / 2 ;

	fileName = "allied.DAT" ;
}


AlliedShip::~AlliedShip(void)						//destructor	
{
}


void AlliedShip::draw(void)							//virtual draw fuction
{	
	glBegin(GL_QUADS); //light blue stripe coordinates
		glColor3f(0.0f, 0.8f, 0.8);
		glVertex3f(-7.0f + pos.X , 0.0f + pos.Y , -100.0f);
		glVertex3f(0.0f + pos.X , 2.0f + pos.Y , -100.0f);
		glVertex3f(4.5f + pos.X , 1.5f + pos.Y , -100.0f);
		glVertex3f(-7.0f + pos.X , 0.0f + pos.Y , -100.0f);
	glEnd();

	glBegin(GL_QUADS); //main blue deck coordinates
		glColor3f(0.0f, 0.3f, 0.8);
		glVertex3f(-7.0f + pos.X , 0.0f + pos.Y , -100.0f);		//lower left
		glVertex3f(-8.5f + pos.X , 3.0f + pos.Y , -100.0f);		//upper left
		glVertex3f(8.5f + pos.X , 1.0f + pos.Y , -100.0f);		//upper right
		glVertex3f(7.0f + pos.X , 0.0f + pos.Y , -100.0f);		//lower right
	glEnd();

	glBegin(GL_QUADS); //cabin windshield coordinates
		glColor3f(1.0f, 0.0f, 0.0);
		glVertex3f(-4.8f + pos.X , 3.0f + pos.Y , -100.0f);
		glVertex3f(-4.2f + pos.X , 3.5f + pos.Y , -100.0f);
		glVertex3f(1.0f + pos.X , 3.5f + pos.Y , -100.0f);
		glVertex3f(0.0f + pos.X , 3.0f + pos.Y , -100.0f);
	glEnd();

	bombs.start.X = turret.X + (3 * cos(RAD*angle) ) ;
	bombs.start.Y = turret.Y + (3 * sin(RAD*angle) ) ;

	glBegin(GL_QUADS); //Turret coordinates
		glColor3f(0.0f, 0.6f, 1.0);
		glVertex3f(turret.X - 0.4, turret.Y, -100.0f);
		glVertex3f(bombs.start.X - 0.25, bombs.start.Y , -100.0f);
		glVertex3f(bombs.start.X + 0.25, bombs.start.Y , -100.0f);
		glVertex3f(turret.X + 0.4, turret.Y, -100.0f);
	glEnd();

	glBegin(GL_QUADS); //main cabin coordinates
		glColor3f(0.4f, 0.0f, 0.6);
		glVertex3f(-6.5f + pos.X , 0.0f + pos.Y , -100.0f);
		glVertex3f(-4.0f + pos.X , 4.0f + pos.Y , -100.0f);
		glVertex3f(4.0f + pos.X , 4.0f + pos.Y , -100.0f);
		glVertex3f(0.0f + pos.X , 0.0f + pos.Y , -100.0f);
	glEnd();

	glBegin(GL_POLYGON); //main Wing coordinates
		glColor3f(0.4f, 0.0f, 0.6);
		glVertex3f(2.0f + pos.X , 0.0f + pos.Y , -100.0f);
		glVertex3f(4.0f + pos.X , 3.0f + pos.Y , -100.0f);
		glVertex3f(11.0f + pos.X , 3.0f + pos.Y , -100.0f);
	glEnd();
}


void AlliedShip::move(char a)								//moving ship
{

	if (DeltaMove >= -12.0 && a == 'a')								//checking left moves
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

	
	
	else if (DeltaMove <= 12.0 && a == 'd')								//checking Right moves
	{
		BottomLeft.X += 0.1 ;
		BottomRight.X += 0.1 ;
		TopLeft.X += 0.1 ;
		TopRight.X += 0.1 ;
		bombs.start.X += 0.1 ;
		turret.X += 0.1 ;
		
		DeltaMove += 0.1 ;
		CurrentPosition = (TopRight + TopLeft) / 2 ;
	}
}


bool AlliedShip::checkLeft()									//checking whether to move ship or not
{
	if ( BottomLeft.X == -7.0 + pos.X )
		return 0 ;

	return 1 ;
}


bool AlliedShip::checkRight()									//checking whether to move ship or not
{
	if ( BottomLeft.X == -7.0 + pos.X )
		return 0 ;

	return 1 ;
}


void AlliedShip::changePower(char a)			//increasing or decreasing power
{

	if ( a == 's' && power < 100 )			
		power++ ;


	else if ( a == 'w' && power > 0 )
		power-- ;
}


void AlliedShip::changeAngle(char a)			//increasing or decreasing power
{

	if ( a == 's' && angle < 180 )
		angle++ ;


	else if ( a == 'w' && angle > 90 )
		angle-- ;
}



void AlliedShip::display_Atr()		//Displaying Attributes on the screen
{
	//drawing the score board
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex3f(37, 30.5, -100);
	glVertex3f(32, 40, -100);
	glVertex3f(55, 40, -100);
	glVertex3f(55, 30.5, -100);
	glEnd();

	char a[20] = "Angle = " ;
	char p[20] = "Power = " ;
	char s[20] = "Score = " ;

	//changing angle ad power in strings
	DEC2STR(angle, a+8);
	DEC2STR(power, p+8);
	DEC2STR(score, s+8);

	glColor3f(1, 1, 1);
	glRasterPos3f(38, 36.5,-99);

	//displaying angle on screen
	for(char *c = a ; *c!='\0';c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);


	glColor3f(0.0, 0.7, 1.0);
	glRasterPos3f(37.5, 34,-99);

	//displaying power on screen
	for(char *c = p ; *c!='\0';c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

	glColor3f(1, 1, 1);
	glRasterPos3f(38.5, 31.5,-99);

	//displaying power on screen
	for(char *c = s ; *c!='\0';c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);

}



void AlliedShip::DisplayHighScore()			//displaying high score
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
	glRasterPos3f(5, 6 ,-99);

	//displaying power on screen
	for(char *c = Scr ; *c!='\0';c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	

	DEC2STR (HScore[1] , Scr);
	glRasterPos3f(5, -1 ,-99);

	//displaying power on screen
	for(char *c = Scr ; *c!='\0';c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);


	DEC2STR (HScore[2] , Scr);
	glRasterPos3f(5, -8 ,-99);

	//displaying power on screen
	for(char *c = Scr ; *c!='\0';c++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
}


void AlliedShip::intialize()
{
	power = 0 ;
	angle = 90 ;

	pos.X = +58.0 ;
	pos.Y = -15.0 ;

	BottomLeft.X = -7.0f + pos.X ;								//lower left
	BottomLeft.Y = 0.0f + pos.Y ;

	TopLeft.X = -8.5f + pos.X ;									//upper left
	TopLeft.Y = 3.0f + pos.Y ;
				
	TopRight.X = 8.5f + pos.X ;									//upper right
	TopRight.Y =  1.0f + pos.Y ;
				
	BottomRight.X = 7.0f + pos.X ;								//lower right
	BottomRight.Y = 0.0f + pos.Y ;

	bombs.currentPos = TopLeft ;						//assigning current position to bomb
	bombs.nxtPos = TopLeft ;
	bombs.start = TopLeft ;

	bombs.start.X += 2 ;
	turret = bombs.start ;
	turret.Y -= 0.1 ;

	CurrentPosition = (BottomRight + BottomLeft) / 2 ;

	score = 0 ;
	DeltaMove = 0 ;

}