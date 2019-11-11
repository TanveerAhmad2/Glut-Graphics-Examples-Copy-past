#include<windows.h>
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <time.h>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <GL/glut.h>
using namespace std;

int x = 0;
int y = 0;
bool down = false;
bool up = false;


void mouse(int button, int state, int ax, int ay)
{
	x = ax;
	y = ay;
	down = state == GLUT_DOWN;
	up = state == GLUT_UP;
}

void motion(int ax, int ay)
{
	x = ax;
	y = ay;
}
class game{
public:
	int OrthoWid;
	int OrthoHei;
	float reshapex;
	float reshapey;
	int WinWid;
	int WinHei;
	int winXPos;
	int winYPos;
	int IIcounter= 0;
	float FieldSizeX;
	float FieldSizeY;
	int delay;
	float PThickness;
	float BallSize;
	float BorderT;
	float MLineT;
	int ScoreL;
	int ScoreR;
	float TextPosX;
	float TextPosY;
	float BallSpeedX;
	float PSpeedY;
	float lvlBallSpeed;
	float lvlreflectorSize;
	int lvlIIrandomize;
	game(){
		WinWid = 650;
		WinHei = 470;
		OrthoWid = 650;
		OrthoHei = 470;
		winXPos = 100;
		winYPos = 100;
		delay = 1;
		PThickness = 5;
		lvlreflectorSize = 1;
		lvlIIrandomize = 1;
		BallSize = 7;
		lvlBallSpeed = 0.000000001;
		FieldSizeX = 600;
		FieldSizeY = 400;
		BorderT = 10;
		MLineT = 5;
		ScoreL = 0;
		ScoreR = 0;
		TextPosX = 0;
		TextPosY = FieldSizeY + 30;
		BallSpeedX = 5;
		PSpeedY = 1;
	}
	void start_settings();
	void win();
	void KeyControl();
	void KeyReset();
	void DrawField();
	void DrawScore();
}settings;

class ball{
public:
	float x;
	float y;
	float vx;
	float vy;
	void move();
	void reflection();
	void draw();
}ball;

class reflector{
public:
	float x, y;
	float vy;
	float size;
	bool Up, Down, hold;
	reflector(){
		vy = 0;
		y = 0;
		Up = false;
		Down = false;
		hold = false;
	}
	void draw();
	void draw2();
	void move();
	void moveII();

}lleft, rright;

void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-settings.OrthoWid, settings.OrthoWid, settings.OrthoHei, -settings.OrthoHei);
	glMatrixMode(GL_MODELVIEW);

	settings.reshapex = (width*1.0) / (settings.WinWid*1.0);
	settings.reshapey = (height*1.0) / (settings.WinHei*1.0);
}

void game::KeyReset(){
	lleft.vy = 0;
	rright.vy = 0;
}

void game::KeyControl(){
	if ((lleft.Up) && (!lleft.Down))lleft.vy = PSpeedY;
	if ((!lleft.Up) && (lleft.Down))lleft.vy = -PSpeedY;
	if ((rright.Up) && (!rright.Down))rright.vy = PSpeedY;
	if ((!rright.Up) && (rright.Down))rright.vy = -PSpeedY;
}

void game::start_settings(){
	lleft.size = 200 / settings.lvlreflectorSize;
	rright.size = 200 * settings.lvlreflectorSize;
	lleft.x = -510;
	rright.x = 510;
	ball.vy = 0;
	ball.vx = 0;
	while (ball.vx == 0) ball.vx = (rand() % 3 - 1)*BallSpeedX*lvlBallSpeed;
	while (ball.vy == 0) ball.vy = (rand() % 3 - 1)*BallSpeedX*lvlBallSpeed;
	ball.x = 0;
	ball.y = 0;
}

void game::win(){
	if ((ScoreL == 3) || (ScoreR == 3)){
		glutTimerFunc(4000, exit, 0);
		settings.delay = 10000;
	}
	if (ball.x < lleft.x + PThickness - (BallSpeedX*2)){
		start_settings();
		ScoreR++;
	}
	if (ball.x > rright.x - PThickness + (BallSpeedX*2)){
		start_settings();
		ScoreL++;
	}
}



void game::DrawField(){

	glColor3f(0, 1, 0);
	glVertex2f(-FieldSizeX - BorderT, -FieldSizeY - BorderT);
	glVertex2f(FieldSizeX + BorderT, -FieldSizeY - BorderT);
	glVertex2f(FieldSizeX + BorderT, -FieldSizeY);
	glVertex2f(-FieldSizeX - BorderT, -FieldSizeY);


	glVertex2f(-FieldSizeX - BorderT, FieldSizeY + BorderT);
	glVertex2f(FieldSizeX + BorderT, FieldSizeY + BorderT);
	glVertex2f(FieldSizeX + BorderT, FieldSizeY);
	glVertex2f(-FieldSizeX - BorderT, FieldSizeY);

	glVertex2f(-FieldSizeX - BorderT, -FieldSizeY - BorderT);
	glVertex2f(-FieldSizeX, -FieldSizeY - BorderT);
	glVertex2f(-FieldSizeX, FieldSizeY + BorderT);
	glVertex2f(-FieldSizeX - BorderT, FieldSizeY + BorderT);

	glVertex2f(FieldSizeX, -FieldSizeY - BorderT);
	glVertex2f(FieldSizeX + BorderT, -FieldSizeY - BorderT);
	glVertex2f(FieldSizeX + BorderT, FieldSizeY + BorderT);
	glVertex2f(FieldSizeX, FieldSizeY + BorderT);

	glColor3f(0, 1, 1);
	for (float i = -FieldSizeY; i <= FieldSizeY; i += 4 * MLineT){
		glVertex2f(-MLineT, i + MLineT);
		glVertex2f(MLineT, i + MLineT);
		glVertex2f(MLineT, i - MLineT);
		glVertex2f(-MLineT, i - MLineT);
	}
}
void STRINGWINNER()
{
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'W');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'I');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'N');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'N');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
}
void game::DrawScore(){
	glRasterPos2f(TextPosX - 50, TextPosY + 20);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0' + ScoreL);
	glRasterPos2f(TextPosX + 30, TextPosY + 20);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '0' + ScoreR);

	if (ScoreL == 3){
		glColor3f(0, 0, 1);
		glRasterPos2f(TextPosX - 400, TextPosY -700);
		STRINGWINNER();

	}
	if (ScoreR == 3){
		glColor3f(1, 0, 0);
		glRasterPos2f(TextPosX + 150, TextPosY - 700);
		STRINGWINNER();
	}
}

void reflector::move(){
	y += 5*vy;
	if (y < -settings.FieldSizeY + size / 2){
		y = -settings.FieldSizeY + size / 2;
		vy = 0;
	}
	if (y > settings.FieldSizeY - size / 2){
		y = settings.FieldSizeY - size / 2;
		vy = 0;
	}
}

void reflector::moveII()
{
	if (rright.y < ball.y) y += 5;
	if (rright.y > ball.y) y -= 5;
	if (y < -settings.FieldSizeY + size / 2)
	{
		y = -settings.FieldSizeY + size / 2;
		vy = 0;
	}
	if (y > settings.FieldSizeY - size / 2)
	{
		y = settings.FieldSizeY - size / 2;
		vy = 0;
	}
}

void reflector::draw(){
	glColor3f(0, 0, 1);
	glVertex2f(x + settings.PThickness, y + size / 2);
	glVertex2f(x + settings.PThickness, y - size / 2);
	glVertex2f(x - settings.PThickness, y - size / 2);
	glVertex2f(x - settings.PThickness, y + size / 2);
}

void reflector::draw2(){
	glColor3f(1, 0, 0);
	glVertex2f(x + settings.PThickness, y + size / 2);
	glVertex2f(x + settings.PThickness, y - size / 2);
	glVertex2f(x - settings.PThickness, y - size / 2);
	glVertex2f(x - settings.PThickness, y + size / 2);
}

void ball::reflection(){
	if ((y <= -settings.FieldSizeY) || (y >= settings.FieldSizeY))vy = -vy;
	if ((x <= lleft.x + settings.PThickness) && (fabs(double(y - lleft.y)) <= lleft.size / 2 + fabs(vy))){
		vx = -vx;
		vy += lleft.vy;
	}
	if ((x >= rright.x - settings.PThickness) && (fabs(double(y - rright.y)) <= rright.size / 2 + fabs(vy))){
		vx = -vx;
		vy += rright.vy;
	}
}

void ball::draw(){
	glColor3f(0, 0, 0);
	glVertex2f(x + settings.BallSize, y + settings.BallSize);
	glVertex2f(x + settings.BallSize, y - settings.BallSize);
	glVertex2f(x - settings.BallSize, y - settings.BallSize);
	glVertex2f(x - settings.BallSize, y + settings.BallSize);
}

void ball::move(){
	x += vx;
	y += vy;
}

void keyboard(unsigned char key, int x, int y){
	switch (key)
	{
	case 'a':
		lleft.Up = true;
		break;
	case 'q':
		lleft.Down = true;
		break;
	}
}

void keyboardUp(unsigned char key, int x, int y){
	switch (key)
	{
	case 'a':
		lleft.Up = false;
		break;
	case 'q':
		lleft.Down = false;
		break;
	}
}

void Timer(int value){

	settings.KeyControl();
	lleft.move();
	if (rand() % settings.lvlIIrandomize == 5) {
		settings.IIcounter= 50;
	}
	settings.IIcounter= settings.IIcounter- 1;

	if (settings.IIcounter> 0)
		rright.moveII();
	ball.move();
	ball.reflection();
	settings.KeyReset();
	settings.win();
	glutPostRedisplay();
	glutTimerFunc(settings.delay, Timer, 0);
}

int check=0;
void STRINGexitpp(){
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'X');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'I');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'T');
}
void STRINGeasy(){
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'S');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'Y');
}
void STRINGmedium(){
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'M');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'E');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'D');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'I');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'U');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'M');
}
void STRINGhard(){
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'H');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'A');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'R');
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, 'D');
}
void paral(int s){
	glBegin(GL_LINES);

	glVertex2f(-600  , -300  );
	glVertex2f(-200  , -300  );

	glVertex2f(-200  , -300  );
	glVertex2f(-200  , -200  );

	glVertex2f(-200  , -200  );
	glVertex2f(-600  , -200  );

	glVertex2f(-600  , -200  );
	glVertex2f(-600  , -300  );


	glVertex2f(-600  , -150  );
	glVertex2f(-200  , - 150  );

	glVertex2f(-200  , -150  );
	glVertex2f(-200  , -50  );

	glVertex2f(-200  , -50  );
	glVertex2f(-600  , -50  );

	glVertex2f(-600  , -50  );
	glVertex2f(-600  , -150  );


	glVertex2f(-600  , 0  );
	glVertex2f(-200  , 0  );

	glVertex2f(-200  , 0  );
	glVertex2f(-200  , 100  );

	glVertex2f(-200  , 100  );
	glVertex2f(-600  , 100  );

	glVertex2f(-600  , 0 );
	glVertex2f(-600  , 100  );

	glVertex2f(-600  , 200  );
	glVertex2f(-200  , 200  );

	glVertex2f(-200  , 200  );
	glVertex2f(-200  , 300  );

	glVertex2f(-200  , 300  );
	glVertex2f(-600  , 300  );

	glVertex2f(-600  , 200  );
	glVertex2f(-600  , 300 );



	glEnd();
}
void STRINGhello(){
	char mystring[100];
	glColor3f(1, 0, 0);


	FILE * ptrFile = fopen("hello.txt", "r");
	fgets(mystring, 47, ptrFile);
	fclose(ptrFile);

	glRasterPos2f(-615, -420);
	for (int i = 0; i < 47; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mystring[i]);


	FILE * ptrFile2 = fopen("choose.txt", "r");
	fgets(mystring, 15, ptrFile2);
	fclose(ptrFile2);
	glRasterPos2f(-615, -380);
	for (int i = 0; i < 15; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mystring[i]);

}
void STRINGback(){
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(400, 465);
	glVertex2f(400, 412);

	glVertex2f(400, 412);
	glVertex2f(608, 412);

	glVertex2f(608, 412);
	glVertex2f(608, 465);

	glVertex2f(608, 465);
	glVertex2f(400, 465);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(398, 463);
	glVertex2f(398, 410);

	glVertex2f(398, 410);
	glVertex2f(608, 410);

	glEnd();

	glColor3f(0, 0, 0);
	glRasterPos2f(448, 450);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'B');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'A');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'C');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'K');
	glColor3f(1, 0, 0);
	glRasterPos2f(450, 452);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'B');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'A');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'C');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'K');

}
void menu(){


	glColor3f(0, 0, 0);
	glRasterPos2f(-472, -228);
	STRINGeasy();

	glColor3f(1, 0, 0);
	glRasterPos2f(-470, -230);
	STRINGeasy();

	glColor3f(0, 0, 0);
	glRasterPos2f(-502, -78);
	STRINGmedium();

	glColor3f(1, 0, 0);
	glRasterPos2f(-500, -80);
	STRINGmedium();


	glColor3f(0, 0, 0);
	glRasterPos2f(-472, 68);
	STRINGhard();

	glColor3f(1, 0, 0);
	glRasterPos2f(-470, 70);
	STRINGhard();

	glRasterPos2f(-430, 160);
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'o');
	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'r');

	glColor3f(0, 0, 0);
	glRasterPos2f(-462, 270);
	STRINGexitpp();

	glColor3f(1, 0, 0);
	glRasterPos2f(-460, 272);
	STRINGexitpp();

	glRasterPos2f(-460, 232);

	paral(0);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);

	glVertex2f(-602   , -302  );
	glVertex2f(-202  , -302  );
	glVertex2f(-602  , -200  );
	glVertex2f(-602  , -302  );


	glVertex2f(-602  , -152  );
	glVertex2f(-202  , -152  );
	glVertex2f(-602  , -52 );
	glVertex2f(-602  , -152  );


	glVertex2f(-602  , 2  );
	glVertex2f(-202  , 2  );
	glVertex2f(-602  , 2  );
	glVertex2f(-602  , 102  );

	glVertex2f(-602, 198);
	glVertex2f(-202, 198);

	glVertex2f(-602, 198);
	glVertex2f(-602, 302);

	glEnd();

	STRINGhello();

	glColor3f(1, 0, 0);
	glPointSize(25);
	glBegin(GL_POINTS);
	if (down)
	{
		float mx = x * 2 - 645; float my = y * 2 - 475;
		if (x > 25 * settings.reshapex && y > 90 * settings.reshapey && x < 225 * settings.reshapex && y < 135 * settings.reshapey) //eazy
		{
			check = 1;
			settings.ScoreL = 0;
			settings.ScoreR = 0;
			rright.y = 0;
			lleft.y = 0;
			settings.lvlBallSpeed = 1;
			settings.lvlIIrandomize = 80;
			settings.lvlreflectorSize = 1;
			settings.start_settings();
		}
		if (x > 25 * settings.reshapex && y > 160 * settings.reshapey && x < 225 * settings.reshapex && y < 212 * settings.reshapey) //medium
		{
			check = 1;
			settings.ScoreL = 0;
			settings.ScoreR = 0;
			rright.y = 0;
			lleft.y = 0;
			settings.lvlBallSpeed = 1.3;
			settings.lvlIIrandomize = 50;
			settings.lvlreflectorSize = 1.3;
			settings.start_settings();
		}
		if (x > 25 * settings.reshapex && y > 235 * settings.reshapey && x < 225 * settings.reshapex && y < 288 * settings.reshapey) //hard
		{
			check = 1;
			settings.ScoreL = 0;
			settings.ScoreR = 0;
			rright.y = 0;
			lleft.y = 0;
			settings.lvlBallSpeed = 1.7;
			settings.lvlIIrandomize = 25;
			settings.lvlreflectorSize = 1.6;
			settings.start_settings();
		}
		if (x > 25 * settings.reshapex && y > 335 * settings.reshapey && x < 225 * settings.reshapex && y < 388 * settings.reshapey) //exit
		{
			glutTimerFunc(250, exit, 0);
		}
	}
	glEnd();
}
void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	if (check == 0)
	{
		menu();
	}
	if (check == 1)
	{
		STRINGback();
		if (down)
		{
			if (x > 530 * settings.reshapex && y > 440 * settings.reshapey && x < 630 * settings.reshapex && y < 466 * settings.reshapey)
			{
				check = 0;
				ball.vx = 0;
				ball.vy = 0;
			}
		}
	glBegin(GL_QUADS);
	rright.draw2();
	lleft.draw();
	ball.draw();
	settings.DrawField();
	glEnd();
	settings.DrawScore();
	}
	glutSwapBuffers();
}

int main(int argc, char ** argv){
	srand(time(NULL));
	settings.start_settings();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(settings.WinWid, settings.WinHei);
	glutInitWindowPosition(settings.winXPos, settings.winYPos);
	glutCreateWindow("Ping-Pong");
	glutDisplayFunc(draw);
	glutTimerFunc(settings.delay, Timer, 0);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMouseFunc(mouse);
	glutPassiveMotionFunc(motion);
	glutReshapeFunc(Reshape);
	glClearColor(1, 1, 1, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-settings.OrthoWid, settings.OrthoWid, settings.OrthoHei, -settings.OrthoHei);
	glutMainLoop();
	return(0);
}
