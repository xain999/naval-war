//////////////////////////////////////// LIBRARIES & CLASSES INCLUDED /////////////////////////////////

#include "AlliedShip.h"
#include "SovietShip.h"
#include "Bomb.h"
#include "glut.h"
#include "imageloader.h"

#include <ctime>
#include <conio.h>
#include <stdlib.h>
#include <Windows.h>

////////////////////////////////////// EXTRA FUNCTIONALITY /////////////////////////////////////////////

#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")		//removing console

#define WIN_WIDTH 1280		//height of screen specified
#define WIN_HEIGHT 720		//width of screen specified

//////////////////////////// Prototype of callback & utility functions ///////////////////////////

Ship *warship[2] ;
Bomb *bomb ;
int rnd ;
bool enter = 0 ;
char deltaMove = ' ' ;
int player = 0 ;
int bombsLeft = 5 ;
int menu = 4 ;
float menu_box = 0.0 ;
int loading = 0;


GLuint _textureId_main_menu ;
GLuint _textureId_help_menu ;
GLuint _textureId_highscore_menu ;
GLuint _textureId_sky_city;
GLuint _textureId_water_city;
GLuint _textureId_sky_jungle;
GLuint _textureId_water_jungle;
GLuint _textureId_sov;
GLuint _textureId_alli;
GLuint _textureId_main;

void Rendering_Game();						//rendering the game
void Rendering_Help_Menu();					//rendering help menu
void Rendering_HighScore_Menu();			//rendering highscore menu
void Rendering_Main_Menu();					//rendering main menu
void Rendering_Loading();					//rendering loading screen
void LoadImages();							//loading images from file
void City_Background();						//placing city background
void Jungle_Background();					//placing jungle background
GLuint loadTexture(Image*);					//image loading function
void drawJungle();							//drawing jungle
void drawCity();							//drawing city
void initGlutEnv( int argc, char *argv[]);	//initializing glut
void handleKeypress(unsigned char, int, int);//handling keys
void Rendering();							//rendering
void handleResize(int, int);				//resizing window
void drawScene();							//drawing ships
void releaseKey(unsigned char, int , int);	//called when a key is released
void processSpecialKeys(int, int, int);		//process extra keys
void Render_Xtras();						//Extra screen material
void initialize();							//initialize game
void Blast();								//blast bomb


///////////////////////////////////// MAIN PROGRAM ///////////////////////////////////////

int main( int argc, char *argv[]){

	warship[0] = new AlliedShip ;	//assigning Allied and soviet ships
	warship[1] = new SovietShip ;
	bomb = new Bomb ;

	srand((unsigned)time(0));

	for (int i = 0 ; i < 5 ; i++)
		rnd = rand() % 2 ;


	//Initialize glut enviroment and create window GUI
	initGlutEnv( argc,argv);


	//Set handler functions for drawing, keypresses, and window resizes
	
	glutDisplayFunc(Rendering);
	glutIdleFunc(Rendering);

	glutKeyboardFunc(handleKeypress);
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardUpFunc(releaseKey);
	glutReshapeFunc(handleResize);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);
	
	//Start the main loop.  
	glutMainLoop();

	return 0;
}

//draw Scene
void drawScene()
{
	for (int i = 0 ; i <2 ; i++)
	{
		glPushMatrix();
		warship[i]->draw() ;
		glPopMatrix();
	}

}



// Setting up glut enviroment so we can use function etc
void initGlutEnv( int argc, char *argv[]){

	//Initialize GLUT enviroment
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	//Set the window size and location
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT); 
	glutInitWindowPosition (0, 0);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //Change the background color

	//Create the window
	glutCreateWindow("Operation Naval War");

	glutFullScreen();	//Fullscreen window

	LoadImages();		//Loading images from file
}


void Rendering()	//choosing the rendering function
{
	if (menu == 0)		//rendering game
		Rendering_Game();
	

	else if (menu == 1)	//rediering main menu
		Rendering_Main_Menu();
	
	
	else if (menu == 2)	//rendering highscore menu
		Rendering_HighScore_Menu();


	else if (menu == 3)	//rendering help menu
		Rendering_Help_Menu();


	else if (menu == 4)	//rendering loading screen
		Rendering_Loading();
}


//Initializes 3D rendering
void Rendering_Game() {

	if (deltaMove == 'a')
		warship[player]->move('a') ;

	else if (deltaMove == 'd')
		warship[player]->move('d') ;

	warship[player]->ChangePosition() ;

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	// Reset transformations
	glLoadIdentity();
	
	warship[0]->display_Atr();
	warship[1]->display_Atr();

	//rendomly draw city or jungle
	if (rnd == 0)
		drawJungle() ;

	else if (rnd == 1)
		drawCity() ;

	if (enter)		//if enter is pressed fire bomb
		warship[player]->Fire();

	//check whether to blast the bomb or not
	if (warship[player]->CheckBomb(rnd, player) && enter == 1)
	{
		//caclulating score
		if (player == 0)
			warship[player]->calculateScore(warship[1]->getPosition()) ;

		else if (player == 1)
			warship[player]->calculateScore(warship[0]->getPosition()) ;


		//change player
		if (player == 1)
			bombsLeft-- ;

	}


	if (player == 0 && bombsLeft != 0)
	{
		glColor3f(0, 0, 1);
		glRasterPos3f(-8, -38,-99);

		//displaying angle on screen
		for(char *c = "Allied's Turn" ; *c!='\0';c++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}

	else if (player == 1 && bombsLeft != 0)
	{
		glColor3f(0.7, 0, 0);
		glRasterPos3f(-8, -38,-99);

		//displaying angle on screen
		for(char *c = "Soviet's Turn" ; *c!='\0';c++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
	}

	else if (bombsLeft == 0)
	{
		if (warship[0]->getScore() > warship[1]->getScore())
		{
			glColor3f(0.7, 0, 0);
			glRasterPos3f(-8, -38,-99);

			//displaying angle on screen
			for(char *c = "Allied Wins!" ; *c!='\0';c++)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
		}


		else if (warship[0]->getScore() < warship[1]->getScore())
		{
			glColor3f(0.7, 0, 0);
			glRasterPos3f(-8, -38,-99);

			//displaying angle on screen
			for(char *c = "Soviet Wins!" ; *c!='\0';c++)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
		}

		else
		{
			glColor3f(0.7, 0, 0);
			glRasterPos3f(-8, -38,-99);

			//displaying angle on screen
			for(char *c = "Match Drawn :(" ; *c!='\0';c++)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
		}
	}


	//draw ships
	drawScene();

	//draw jungle or city
	if (rnd == 0)
		Jungle_Background();

	else if (rnd == 1)
		City_Background();

	if (warship[player]->CheckBomb(rnd, player) && enter == 1)
	{
		Blast() ;
	}
	
	glutSwapBuffers();


	if (warship[player]->CheckBomb(rnd, player) && enter == 1)
	{
		enter = 0 ;
		player++ ;

		if (player > 1)
			player = 0 ;

		Sleep(500);
	}
		

	//go to menu at the end of the game
	if (bombsLeft == 0)
	{
		menu = 1 ;
		warship[0]->SaveToFile();
		warship[1]->SaveToFile();

		initialize();
		Sleep(5000);
	}
}

//Called when the window is resized
void handleResize(int w, int h) {
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
	
	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(45.0,                  //The camera angle
				   (double)w / (double)h, //The width-to-height ratio
				   1.0,                   //The near z clipping coordinate
				   200.0);                //The far z clipping coordinate
}


//Called when a key is pressed
void handleKeypress(unsigned char key, //The key that was pressed
					int x, int y) {    //The current mouse coordinates

	switch (key) {

		case 'a' :						//moving left if possible
				deltaMove = 'a' ;
			break ;

		case 'd' :						//moving right if possible
				deltaMove = 'd' ;
			break ;

		case 8 :
			if (menu == 2 || menu == 3)	//if backspace is pressed go to main menu
				menu = 1;
			break ;

		case 13 :
			if (menu == 0)	//fire
				enter = 1 ;

			else if (menu == 1)	//select option
			{
				if (menu_box > -1.0)
					menu = 0 ;

				else if (menu_box <= -6.0 && menu_box >= -7.0)
					menu = 2 ;

				else if (menu_box <= -12.0 && menu_box >= -13.0)
					menu = 3 ;

				else if (menu_box <= -34)
				{
					delete warship[0] ;
					delete warship[1] ;
					exit(0) ;
				}
			}
			break;

		case 27: //Escape key
			menu = 1; //Go to main menu
	}
}



void releaseKey(unsigned char key, int x, int y) {		//called when a key is released

	switch (key) {
		case 'a' :
		case 'd' : deltaMove = ' ' ;
			break;
	}
}



void processSpecialKeys(int key, int xx, int yy) {	//handle special keys

	switch (key) {
		case GLUT_KEY_LEFT :	
			
			//increasing power if possible

			if(menu == 0)
				warship[player]->changePower('s');
			break;

		case GLUT_KEY_RIGHT :			
			
			//decreasing power if possible
			if (menu == 0)
				warship[player]->changePower('w');
			break;

		case GLUT_KEY_UP :		

			if (menu == 0)				//increasing angle if possible
				warship[player]->changeAngle('w');

			else if (menu == 1 && menu_box < -1.0)	//moving box
			{
				if (menu_box <= -13)
					menu_box += 35.6 ;

				else
					menu_box += 6.3 ;
			}
			break;

		case GLUT_KEY_DOWN :

			if (menu == 0)				//decreasing angle if possible
				warship[player]->changeAngle('s');

			else if (menu == 1 && menu_box > -45)	//moving box
			{
				if (menu_box < -7)
					menu_box -= 35.6 ;

				else
					menu_box -= 6.3 ;
			}
			break;
	}
}


//Draws the Jungle
void drawJungle() {

	Render_Xtras();

	for (int X=0; X<75; X=X+5)	//tree Loop
	{
	
	glBegin(GL_QUADS); //tree trunk
		glColor3f(0.3, 0.2, 0.0);
		glVertex3f(-35+X, -15, -100);
		glVertex3f(-35+X, -13, -100);
		glVertex3f(-34+X, -13, -100);
		glVertex3f(-34+X, -15, -100);
	glEnd();

	glBegin(GL_TRIANGLES); //green part tree
		glColor3f(0.0, 0.3, 0.0);
		glVertex3f(-36.5+X, -13, -100.0);
		glVertex3f(-34.5+X, -7, -100.0);
		glVertex3f(-32.5+X, -13, -100.0);
	glEnd();
	
	}		//end of loop


	glBegin(GL_TRIANGLES); //main green mountain
		glColor3f(0.0, 0.05, 0.0);
		glVertex3f(-25, -15, -100.0);
		glColor3f(0.0, 0.2, 0.0);
		glVertex3f(0.0, 30, -100.0);
		glColor3f(0.0, 0.05, 0.0);
		glVertex3f(25, -15, -100.0);
	glEnd();

	glBegin(GL_TRIANGLES); //secondary left mountain
		glColor3f(0.0, 0.15, 0.0);
		glVertex3f(-30, -15, -100.0);
		glVertex3f(-15, 20, -100.0);
		glColor3f(0.0, 0.7, 0.0);
		glVertex3f(0, -15, -100.0);
	glEnd();

	glBegin(GL_TRIANGLES); //secondary right mountain
		glColor3f(0.0, 0.7, 0.0);
		glVertex3f(0, -15, -100.0);
		glColor3f(0.0, 0.1, 0.0);
		glVertex3f(15, 25, -100.0);
		glVertex3f(30, -15, -100.0);
	glEnd();

	glBegin(GL_QUADS); //beach
		glColor3f(0.01, 0.01, 0.0);
		glVertex3f(-30, -18, -100);
		glColor3f(0.2, 0.2, 0.0);
		glVertex3f(-37, -15, -100);
		glVertex3f(37, -15, -100);
		glColor3f(0.01, 0.01, 0.0);
		glVertex3f(30, -18, -100);
	glEnd();

	glColor3f(1, 1, 1);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_water_jungle);
	
	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBegin(GL_QUADS); //sea
		//glColor3f(0.0, 0.5, 0.7);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-100, -43, -100.0);
		//glColor3f(0.0, 0.7, 0.7);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-100, -15, -100.0);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(80, -15, -100.0);
		//glColor3f(0.0, 0.5, 0.7);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(80, -43, -100.0);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}


//Draws the City
void drawCity() {
	
	Render_Xtras();

	//from left, we have
	glBegin(GL_QUADS); //1st building
		glColor3f(0.3, 0, 0);
		glVertex3f(-33, -15, -100);
		glColor3f(0.7,0.3, 0);
		glVertex3f(-33, 0, -100);
		glColor3f(0.3, 0, 0);
		glVertex3f(-26, 0, -100);
		glVertex3f(-26, -15, -100);
	glEnd();

	glBegin(GL_QUADS); //2nd building
		glColor3f(0, 0.2, 0);
		glVertex3f(-26, -15, -100);
		glColor3f(0.7, 0.3, 0);
		glVertex3f(-26, -5, -100);
		glColor3f(0, 0.2, 0);
		glVertex3f(-22.2, -5, -100);
		glVertex3f(-22.2, -15, -100);
	glEnd();

	glBegin(GL_QUADS); //3rd building
		glColor3f(0, 0.4, 0.5);
		glVertex3f(-25, -15, -100);
		glColor3f(0.7, 0.3, 0);
		glVertex3f(-25, 15, -100);
		glColor3f(0, 0.4, 0.5);
		glVertex3f(-18, 15, -100);
		glVertex3f(-18, -15, -100);
	glEnd();

	glBegin(GL_QUADS); //4th building
		glColor3f(0.3, 0, 0);
		glVertex3f(-20, -15, -100);
		glColor3f(0.7, 0.3, 0);
		glVertex3f(-20, 20, -100);
		glColor3f(0.3, 0, 0);
		glVertex3f(-12, 20, -100);
		glVertex3f(-12, -15, -100);
	glEnd();

	glBegin(GL_QUADS); //5th building
		glColor3f(0.6, 0, 0);
		glVertex3f(-11, -15, -100);
		glColor3f(0.7, 0.3, 0);
		glVertex3f(-11, 30, -100);
		glColor3f(0.6, 0, 0);
		glVertex3f(-4, 22, -100);
		glVertex3f(-4, -15, -100);
	glEnd();

	glBegin(GL_QUADS); //H-dash
		glColor3f(0.6, 0, 0);
		glVertex3f(-4, 14, -100);
		glVertex3f(-4, 17, -100);
		glColor3f(0, 0, 0);
		glVertex3f(4, 17, -100);
		glVertex3f(4, 14, -100);
	glEnd();

	glBegin(GL_TRIANGLES); //X-60 dash
		glColor3f(0, 0, 0);
		glVertex3f(-4, -15, -100);
		glVertex3f(4, 14, -100);
		glVertex3f(-1, -15, -100);
	glEnd();

	glBegin(GL_TRIANGLES); //X-120 building
		glColor3f(0.6, 0, 0);
		glVertex3f(1, -15, -100);
		glVertex3f(-4, 14, -100);
		glVertex3f(4, -15, -100);
	glEnd();

	glBegin(GL_QUADS); //7th building
		glColor3f(0, 0.2, 0);
		glVertex3f(10, -15, -100);
		glColor3f(0.7, 0.3, 0);
		glVertex3f(10, 23, -100);
		glColor3f(0, 0.2, 0);
		glVertex3f(19, 23, -100);
		glVertex3f(19, -15, -100);
	glEnd();

	glBegin(GL_QUADS); //6th building
		glColor3f(0, 0, 0);
		glVertex3f(4, -15, -100);
		glColor3f(0.7, 0.3, 0);
		glVertex3f(4, 22, -100);
		glColor3f(0, 0, 0);
		glVertex3f(11, 30, -100);
		glVertex3f(11, -15, -100);
	glEnd();

	glBegin(GL_TRIANGLES); //8th building
		glColor3f(0.7, 0.3, 0);
		glVertex3f(20, -15, -100);
		glVertex3f(20, 17, -100);
		glColor3f(1, 1, 0.0);
		glVertex3f(27.5, -15, -100);
	glEnd();

	glBegin(GL_QUADS); //9th building
		glColor3f(0, 0, 0);
		glVertex3f(25, -15, -100);
		glColor3f(0.7, 0.3, 0);
		glVertex3f(25, 13, -100);
		glColor3f(0, 0, 0);
		glVertex3f(30.5, 13, -100);
		glVertex3f(30.5, -15, -100);
	glEnd();

	glBegin(GL_QUADS); //10th building
		glColor3f(0.2, 0.2, 0.2);
		glVertex3f(30, -15, -100);
		glVertex3f(30, 8, -100);
		glVertex3f(33.5, 8, -100);
		glVertex3f(33.5, -15, -100);
	glEnd();

	glBegin(GL_QUADS); //beach
		glColor3f(0.3, 0.3, 0.0);
		glVertex3f(-30, -18, -100);
		glColor3f(0.6, 0.6, 0.0);
		glVertex3f(-37, -15, -100);
		glVertex3f(37, -15, -100);
		glColor3f(0.3, 0.3, 0.0);
		glVertex3f(30, -18, -100);
	glEnd();

	glColor3f(1, 1, 1);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_water_city);
	
	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBegin(GL_QUADS); //sea
		//glColor3f(0.0, 0.5, 0.7);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-97, -43, -100.0);
		//glColor3f(0.0, 0.7, 0.7);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-97, -15, -100.0);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(100, -15, -100.0);
		//glColor3f(0.0, 0.5, 0.7);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(100, -43, -100.0);
	glEnd();

	glDisable(GL_TEXTURE_2D);

}


GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}



void City_Background()
{
	glColor3f(1, 1, 1);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_sky_city);
	
	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	
	//glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-140, -135, -100);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-100, 100, -100);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(100, 100, -100);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(140, -135, -100);
	
	glEnd();

	glDisable(GL_TEXTURE_2D);
}



void Jungle_Background()
{
	glColor3f(1, 1, 1);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_sky_jungle);
	
	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBegin(GL_QUADS);
	
	//glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-80, -15, -100);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-80, 50, -100);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(80, 50, -100);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(80, -15, -100);
	
	glEnd();

	glDisable(GL_TEXTURE_2D);
}



void LoadImages()	//loading images from files
{
	Image* image_water_city = loadBMP("Textures_f/eve_water.bmp");		//loading water for city
	_textureId_water_city = loadTexture(image_water_city);
	delete image_water_city;

	Image* image_sky_city = loadBMP("Textures_f/eve_sky.bmp");			//loading sky for city
	_textureId_sky_city = loadTexture(image_sky_city);
	delete image_sky_city;

	Image* image_sky_jungle = loadBMP("Textures_f/night_sky.bmp");		//loading sky for jungle
	_textureId_sky_jungle = loadTexture(image_sky_jungle);
	delete image_sky_jungle;

	Image* image_water_jungle = loadBMP("Textures_f/night_water.bmp");		//loading water for jungle
	_textureId_water_jungle = loadTexture(image_water_jungle);
	delete image_water_jungle;

	Image* image_main_menu = loadBMP("Textures_f/main_menu.bmp");		//loading Main Menu
	_textureId_main_menu = loadTexture(image_main_menu);
	delete image_main_menu ;

	Image* image_highscore_menu = loadBMP("Textures_f/hi_score_scr.bmp");		//loading High score screen
	_textureId_highscore_menu = loadTexture(image_highscore_menu);
	delete image_highscore_menu ;

	Image* image_help_menu = loadBMP("Textures_f/help_scr.bmp");		//loading Help screen
	_textureId_help_menu = loadTexture(image_help_menu);
	delete image_help_menu ;
	
	Image* image_sov = loadBMP("Textures_f/soviet.bmp");		//loading soviet logo
	_textureId_sov = loadTexture(image_sov);
	delete image_sov ;

	Image* image_alli = loadBMP("Textures_f/allied.bmp");		//loading allied logo
	_textureId_alli = loadTexture(image_alli);
	delete image_alli ;

	Image* image_load = loadBMP("Textures_f/_title.bmp");		//loading title screen
	_textureId_main = loadTexture(image_load);
	delete image_load ;
}



void Rendering_Main_Menu()		//rendering main munu
{
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	// Reset transformations
	glLoadIdentity();

	//drawing menu box
	glLineWidth(4.0);
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0.7);
	glVertex3f(35.2, 11 + menu_box, -100);
	glColor3f(0.8, 0, 0);
	glVertex3f(35.2, 16 + menu_box, -100);
	glColor3f(0, 0, 0.7);
	glVertex3f(65, 16 + menu_box, -100);
	glColor3f(0.8, 0, 0);
	glVertex3f(65, 11 + menu_box, -100);
	glEnd();

	glColor3f(1, 1, 1);

	//drawing picture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_main_menu);
	
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBegin(GL_QUADS);
	
	//coordinates of picture
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-75, -42, -100);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-75, 42, -100);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(75, 42, -100);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(75, -42, -100);
	
	glEnd();

	glDisable(GL_TEXTURE_2D);


	
	glutSwapBuffers();
}



void Rendering_Help_Menu()		//rendering help menu
{
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	// Reset transformations
	glLoadIdentity();

	
	glColor3f(1, 1, 1);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_help_menu);
	
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBegin(GL_QUADS);
	
	//glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-75, -42, -100);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-75, 42, -100);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(75, 42, -100);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(75, -42, -100);
	
	glEnd();

	glDisable(GL_TEXTURE_2D);


	
	glutSwapBuffers();
}


		
void Rendering_HighScore_Menu()		//rendering HighScore munu
{
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	// Reset transformations
	glLoadIdentity();

	//////////////////////////////////////////////////////////////////////////////
	glColor3f(0, 0, 0);

	glBegin(GL_QUADS);					//1st highscore box

	glVertex3f(-1, 4, -100);
	glVertex3f(-1, 9, -100);
	glVertex3f(15, 9, -100);
	glVertex3f(15, 4, -100);
	
	glEnd();

	glBegin(GL_QUADS);					//2nd highscore box

	glVertex3f(-1, -3, -100);
	glVertex3f(-1, 2, -100);
	glVertex3f(15, 2, -100);
	glVertex3f(15, -3, -100);
	
	glEnd();
	
	glBegin(GL_QUADS);					//3rd highscore box

	glVertex3f(-1, -10, -100);
	glVertex3f(-1, -5, -100);
	glVertex3f(15, -5, -100);
	glVertex3f(15, -10, -100);
	
	glEnd();


	glBegin(GL_QUADS);					//4th highscore box

	glVertex3f(-1, -20.5, -100);
	glVertex3f(-1, -15.5, -100);
	glVertex3f(15, -15.5, -100);
	glVertex3f(15, -20.5, -100);
	
	glEnd();


	glBegin(GL_QUADS);					//5th highscore box

	glVertex3f(-1, -27, -100);
	glVertex3f(-1, -22, -100);
	glVertex3f(15, -22, -100);
	glVertex3f(15, -27, -100);
	
	glEnd();


	glBegin(GL_QUADS);					//6th highscore box

	glVertex3f(-1, -34, -100);
	glVertex3f(-1, -29, -100);
	glVertex3f(15, -29, -100);
	glVertex3f(15, -34, -100);
	
	glEnd();

	warship[0]->DisplayHighScore() ;
	warship[1]->DisplayHighScore() ;

	///////////////////////////////////////////////////////////////////////
	
	glColor3f(1, 1, 1);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_highscore_menu);
	
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBegin(GL_QUADS);
	
	//glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-75, -42, -100);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-75, 42, -100);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(75, 42, -100);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(75, -42, -100);
	
	glEnd();

	glDisable(GL_TEXTURE_2D);


	
	glutSwapBuffers();
}


void Rendering_Loading()		//loading screen
{
		// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	// Reset transformations
	glLoadIdentity();

	
	glColor3f(1, 1, 1);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_main);
	
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBegin(GL_QUADS);
	
	//glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-75, -42, -100);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-75, 42, -100);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(75, 42, -100);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(75, -42, -100);
	
	glEnd();

	glDisable(GL_TEXTURE_2D);

	//////////////////////////////////////////////////////////////////////////////

	glColor3f(1, 1, 1);

	if ( loading == 0 )
	{
		glBegin(GL_QUADS);
	
		glVertex3f(-70, -38, -99);
		glVertex3f(-70, -37, -99);
		glVertex3f(-60, -37, -99);
		glVertex3f(-60, -38, -99);
	
		glEnd();
	}

	if ( loading == 1 )
	{
		glBegin(GL_QUADS);
	
		glVertex3f(-70, -38, -99);
		glVertex3f(-70, -37, -99);
		glVertex3f(-10, -37, -99);
		glVertex3f(-10, -38, -99);
	
		glEnd();
	}


	if ( loading == 2 )
	{
		glBegin(GL_QUADS);
	
		glVertex3f(-70, -38, -99);
		glVertex3f(-70, -37, -99);
		glVertex3f(40, -37, -99);
		glVertex3f(40, -38, -99);
	
		glEnd();
	}
	
	if ( loading == 3 )
	{
		glBegin(GL_QUADS);
	
		glVertex3f(-70, -38, -99);
		glVertex3f(-70, -37, -99);
		glVertex3f(70, -37, -99);
		glVertex3f(70, -38, -99);
	
		glEnd();
	}

	//////////////////////////////////////////////////////////////////////////////
	
	glutSwapBuffers();

	if (loading == 3)
	{
		Sleep(1500);
		menu = 1 ;
	}

	else
	{
		Sleep(1000);
		loading++ ;
	}
}


void initialize()
{
	player = 0 ;
	bombsLeft = 5 ;

	rnd = rand() % 2 ;

	warship[0]->intialize();
	warship[1]->intialize();
}


void Render_Xtras()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_sov);
	
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	
	//coordinates of soviet logo
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-70, 25, -100);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-70, 40, -100);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-55, 40, -100);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-55, 25, -100);
	
	glEnd();
	glDisable(GL_TEXTURE_2D);

	////////////////////////////////////////////////////////////////////
	
	glBegin(GL_QUADS);					//Box at the bottom, Showing the concerned player's turn

	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-18, -42, -100);
	glColor3f(1, 1, 1);
	glVertex3f(-12, -34, -100);
	glColor3f(1, 1, 1);
	glVertex3f(12, -34, -100);
	glColor3f(0, 0.0, 0);
	glVertex3f(18, -42, -100);
	
	glEnd();
	////////////////////////////////////////////////////////////////////

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId_alli);
	
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	
	//coordinates of allied logo
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(55, 25, -100);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(55, 40, -100);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(70, 40, -100);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(70, 25, -100);
	
	glEnd();

	glDisable(GL_TEXTURE_2D);
}


void Blast()					//Blast function, Renders blast when collision is detected.... 
{
	point temp = warship[player]->getBombPosition();

	glColor3f(0.9, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);
 
   for (int i=0; i < 360; i++)
   {
      float degInRad = i*(3.14/180);
	  glVertex3f(cos(degInRad)*2.5 + temp.getX() , sin(degInRad)*2.5 + temp.getY() , -99.8);
   }
 
   glEnd();

	glColor3f(1, 0.4, 0.0);
	glBegin(GL_TRIANGLE_FAN);
 
   for (int i=0; i < 360; i++)
   {
      float degInRad = i*(3.14/180);
	  glVertex3f(cos(degInRad)*4 + temp.getX() , sin(degInRad)*4 + temp.getY() , -99.8);
   }
 
   glEnd();

   	glColor3f(0.9, 0.9, 0.0);
	glBegin(GL_TRIANGLE_FAN);
 
   for (int i=0; i < 360; i++)
   {
      float degInRad = i*(3.14/180);
	  glVertex3f(cos(degInRad)*4.5 + temp.getX() , sin(degInRad)*4.5 + temp.getY() , -99.8);
   }
 
   glEnd();
}