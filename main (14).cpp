#include<windows.h>
#include <cmath>
#include <string.h>
#include <sstream>
#include <Windows.h>
#include <MMSystem.h>
//classes
#include "Ship.h"
#include "health.h"
#define GLUT_KEY_ESCAPE 27
// Scale factor
const int scale = 75;
// Window proportions 16:9
const int width = 16 * scale;
const int height = 9 * scale;
// Constants
const int numberOfTextures = 2;
const int movement = 20;
const int font = (int)GLUT_BITMAP_9_BY_15;
// Variables
int score = 0;
int bossHealth = 500;
int bossHealthOld = bossHealth;
int playerHealth = 10;
// For changing the frames
int frame0 = 0;
int frame1 = 1;
int frameBoss = 0;
int frameDmgFrame = 0;
int dmgCounterDeath = 25;
int frameDefenders[3] = { 0,0,0 };
bool defenderLaserFrame[3] = { 0, 0, 0 };
bool spaceFlag = 0;
bool starFlag = 1;
bool blockFlag = 0;
bool barrelRollRight = 0;
bool barrelRollLeft = 0;
bool powerUpFlag = 0;
bool energyUpFlag = 0;
bool timerMovingBlock = 0;
bool movingBlock = 0;
bool vCount = 0;
float playerX = width / 2 - 100;
float playerY = 20;
float playerX1 = width / 2 - 100;
float playerY1 = 20;
float bossX = width / 2 - 100;
float bossY = height - 200;
float bossXOld = bossX;
float bossYOld = bossY;
float defenderX[3] = { width / 2 - 100, width / 2 - 300 , width / 2 - 500 };
float defenderY[3] = { height - 300 , height - 300 , height - 300 };
float blockX = bossX + 65;
float blockY = bossY;
float powerUpX = (width / 2) + 200;
float powerUpY = height - 100;
//energyUpFlag
float energyUpX = (width / 2) + 200;
float energyUpY = height - 100;
float defenderLaserX[3] = { defenderX[0], defenderX[1], defenderX[2] };
float defenderLaserY[3] = { defenderY[0] + 65, defenderY[1] + 65, defenderY[2] + 65 };
float laserX[4] = { playerX1, playerX1,playerX1,playerX1 };
float laserY[4] = { playerY1, playerY1,playerY1,playerY1 };
int p0[2][2];
int p1[2][2];
int p2[2][2];
int p3[2][2];
float t[2] = { 1.0f,1.0f };

int gameState = 0; // 0 - Start menu // 1 - Game // 2 - Game Over
				   // Functions

int*bezier(float, int*, int*, int*, int*);
void idle();
void display();
void key(unsigned char, int, int);
void timer(int);


using namespace std;
template <typename T>
std::string to_string(T value)
{
	std::ostringstream os;
	os << value;
	return os.str();
}
float RandomNumber(float Min, float Max)
{
	return ((float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
}


void drawstars()
{
	glPointSize(RandomNumber(0, 4));
	glPushMatrix();
	glTranslated(RandomNumber(0, 2000), RandomNumber(0, 1000), 0);
	glColor3f(1, 1, 1);
	glBegin(GL_POINTS);
	glVertex3d(0, 0, 1);
	glEnd();
	glPopMatrix();
}

void writeString(float x, float y, float z, void *font, string line)
{
	glPushMatrix();
	char c;
	glRasterPos3f(x, y, z);
	for (int i = 0; i<line.size(); i++)
	{
		c = line.at(i);
		glutBitmapCharacter(font, c);
	}
	glPopMatrix();
}

int* bezier(float t, int* p0, int* p1, int* p2, int* p3)
{
	int res[2];
	res[0] = pow((1 - t), 3)*p0[0] + 3 * t*pow((1 - t), 2)*p1[0] + 3 * pow(t, 2)*(1 - t)*p2[0] + pow(t, 3)*p3[0];
	res[1] = pow((1 - t), 3)*p0[1] + 3 * t*pow((1 - t), 2)*p1[1] + 3 * pow(t, 2)*(1 - t)*p2[1] + pow(t, 3)*p3[1];
	return res;
}
float defenderMovementConstant = 0.0008;
int delayCounter = 0;
int healthDelayCounter = 0;
bool defenderflags[3];
void idle()
{
	if (bossHealth <= 0)
	{
		score += 50;
		frameDmgFrame = 2;
		dmgCounterDeath = 100;
		bossHealthOld *= 2;
		bossHealth = bossHealthOld;
	}
	//Game Over Screen
	if (playerHealth < 0)
	{
		gameState = 2;
		playerX1 = width / 2 - 100;
		playerY1 = 20;
		playerHealth = 10;
		frame1 = 1;
		bossHealth = 500;
		bossHealthOld = bossHealth;
	}
	if (gameState == 1)
	{
		if (energyUpFlag)
		{
			if (energyUpY > 0)
			{
				energyUpY -= 0.00005;
			}
			else
			{
				energyUpFlag = 0;
				energyUpY = height - 100;
			}
		}

		if (powerUpFlag)
		{
			if (powerUpY > 0)
			{
				powerUpY -= 0.00005;
				//cout << powerUpY << "\n";
			}
			else
			{
				powerUpFlag = 0;
				powerUpY = height - 100;
			}
		}
		//Defenders

		if (defenderX[0] < 100)
			defenderflags[0] = 0;
		if (defenderX[0] > 900)
			defenderflags[0] = 1;
		if (defenderX[0] >= 0 && !defenderflags[0])
		{
			frameDefenders[0] = 2;
			defenderX[0] += defenderMovementConstant;

		}
		if (defenderX[0] <= width && defenderflags[0])
		{
			frameDefenders[0] = 1;
			defenderX[0] -= defenderMovementConstant;

		}

		if (defenderX[1] < 50)
			defenderflags[1] = 0;
		if (defenderX[1] > 1000)
			defenderflags[1] = 1;
		if (defenderX[1] >= 0 && !defenderflags[1])
		{
			frameDefenders[1] = 2;
			defenderX[1] += defenderMovementConstant;

		}
		if (defenderX[1] <= width && defenderflags[1])
		{
			frameDefenders[1] = 1;
			defenderX[1] -= defenderMovementConstant;

		}


		if (defenderX[2] < 10)
			defenderflags[2] = 0;
		if (defenderX[2] > 1100)
			defenderflags[2] = 1;
		if (defenderX[2] >= 0 && !defenderflags[2])
		{
			frameDefenders[2] = 2;
			defenderX[2] += defenderMovementConstant;

		}
		if (defenderX[2] <= width && defenderflags[2])
		{
			frameDefenders[2] = 1;
			defenderX[2] -= defenderMovementConstant;

		}
		if (defenderLaserFrame[0]) {
			defenderLaserY[0] -= defenderMovementConstant;
		}
		if (defenderLaserFrame[1]) {
			defenderLaserY[1] -= defenderMovementConstant;
		}
		if (defenderLaserFrame[2]) {
			defenderLaserY[2] -= defenderMovementConstant;
		}
		//
		//cout << delayCounter<<"\n";
		//defenderLaserFrame[0]
		if (delayCounter == 1000000) {
			delayCounter = 0;
			if ((RandomNumber(0, 10) > 5) && !blockFlag)
			{
				//cout << "hi";
				blockFlag = 1;
				blockY = bossY;
				blockX = bossX + 65;
			}
			if ((RandomNumber(0, 10) > 5) && !defenderLaserFrame[0])
			{
				defenderLaserFrame[0] = 1;
				defenderLaserX[0] = defenderX[0];
				defenderLaserY[0] = defenderY[0] - 35;
			}
			if ((RandomNumber(0, 10) > 5) && !defenderLaserFrame[1])
			{
				defenderLaserFrame[1] = 1;
				defenderLaserX[1] = defenderX[1];
				defenderLaserY[1] = defenderY[1] - 35;
			}
			if ((RandomNumber(0, 10) > 5) && !defenderLaserFrame[2])
			{
				defenderLaserFrame[2] = 1;
				defenderLaserX[2] = defenderX[2];
				defenderLaserY[2] = defenderY[2] - 35;
			}
			//energyUp
			if (healthDelayCounter >= 10)
			{
				healthDelayCounter = 0;
				if ((RandomNumber(0, 10) > 9) && !energyUpFlag)
				{
					//cout << powerUpFlag << "\n";
					energyUpX = RandomNumber(0, width);
					energyUpFlag = 1;
				}
			}
			healthDelayCounter++;
			if ((RandomNumber(0, 10) > 9) && !powerUpFlag && frame1 != 3)
			{
				//cout << powerUpFlag << "\n";
				powerUpX = RandomNumber(0, width);
				powerUpFlag = 1;
			}
		}
		int* bezierRes;

		//Boss Movement
		bezierRes = bezier(t[1], p0[1], p1[1], p2[1], p3[1]);
		bossXOld = bossX;
		bossYOld = bossY;
		bossX = bezierRes[0];
		bossY = bezierRes[1];
		if (bossX == bossXOld)
		{
			//frameBoss = 0;
		}
		if (bossX > bossXOld)
		{
			frameBoss = 2;
		}
		if (bossX < bossXOld)
		{
			frameBoss = 1;
		}


		if (blockFlag && blockY>0)
		{
			blockY -= 0.0005;

		}
		else
		{
			blockFlag = 0;

		}
		delayCounter++;
	}
}
bool gamerOver = 1;
bool gameRenew = 0;
bool scoreReset = 0;
bool switchGameOver = 1;
int dmgCounter = 0;
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	if (gameState == 0)
	{
		writeString(width / 2 - 300, height / 2, 0, (void *)font, "Press Any Button to start the game.");
	}
	if (gameState == 2)
	{
		scoreReset = 1;
		std::string scoreDisplay = "Score : " + to_string(score);
		writeString(width / 2 - 300, height / 2 + 50, 0, (void *)font, "GAME OVER");
		writeString(width / 2 - 300, height / 2 + 0, 0, (void *)font, scoreDisplay);
		writeString(width / 2 - 300, height / 2 - 50, 0, (void *)font, "HAVE A SECOND CHANCE? Press Cancel.");
	}
	for (int i = 0; i < 200; i = i++) {
		drawstars();
	}
	if (gameState == 1)
	{
		if (scoreReset)
		{
			score = 0;
			scoreReset = 0;
		}
		std::string scoreDisplay = "Score : " + to_string(score);
		writeString(100, height - 50, 0, (void *)font, scoreDisplay);
		Ship ship(playerX1, playerY1, frame0, playerHealth);
		ship.draw();
		Boss boss(bossX, bossY, frameBoss, frameDmgFrame, bossHealth);
		boss.draw();
		Health bossHealthBar(0, 0, 1);
		bossHealthBar.draw(0, bossHealth);
		Health playerHealthBar(0, 30, 1);
		playerHealthBar.draw(1, playerHealth);
		Obstacle defender1(defenderX[0], defenderY[0], frameDefenders[0]);
		defender1.draw(2);
		Obstacle defender2(defenderX[1], defenderY[1], frameDefenders[1]);
		defender2.draw(2);
		Obstacle defender3(defenderX[2], defenderY[2], frameDefenders[2]);
		defender3.draw(2);
		//cout << "R : " << barrelRollRight << "\n";
		//cout << "L : " << barrelRollLeft << "\n";
		/*if (bossX < 0 || bossX > width - 150)
		{
			bossX = width / 2 - 100;
		}*/
		if (bossY < 0 || bossY > height )
		{
			bossY = height - 200;
			t[1] = 0;
		}
		if (ship.collideWithObstacle(defender1))
		{
			if (!barrelRollLeft || !barrelRollRight)
				playerHealth -= 1;
		}
		if (ship.collideWithObstacle(defender2))
		{
			if (!barrelRollLeft || !barrelRollRight)
				playerHealth -= 1;
		}
		if (ship.collideWithObstacle(defender3))
		{
			if (!barrelRollLeft || !barrelRollRight)
				playerHealth -= 1;
		}

		if (defenderLaserFrame[0])
		{
			Obstacle defender1Laser(defenderLaserX[0], defenderLaserY[0], defenderLaserFrame[1]);
			defender1Laser.draw(1);

			if (ship.collideWithObstacle(defender1Laser))
			{
				if (!barrelRollLeft || !barrelRollRight)
					playerHealth -= 1;
				defenderLaserFrame[0] = 0;
			}
			if (defender1Laser.getYMax() < 0)
			{
				defenderLaserFrame[0] = 0;
			}
		}

		if (defenderLaserFrame[1])
		{
			Obstacle defender2Laser(defenderLaserX[1], defenderLaserY[1], defenderLaserFrame[1]);
			defender2Laser.draw(1);

			if (ship.collideWithObstacle(defender2Laser))
			{
				if (!barrelRollLeft || !barrelRollRight)
					playerHealth -= 1;
				defenderLaserFrame[1] = 0;
			}
			if (defender2Laser.getYMax() < 0)
			{
				defenderLaserFrame[1] = 0;
			}
		}

		if (defenderLaserFrame[2])
		{
			Obstacle defender3Laser(defenderLaserX[2], defenderLaserY[2], defenderLaserFrame[2]);
			defender3Laser.draw(1);

			if (ship.collideWithObstacle(defender3Laser))
			{
				if (!barrelRollLeft || !barrelRollRight)
					playerHealth -= 1;
				defenderLaserFrame[2] = 0;
			}
			if (defender3Laser.getYMax() < 0)
			{
				defenderLaserFrame[2] = 0;
			}
		}
		//
		if (ship.collideWithBoss(boss))
		{
			if (!barrelRollLeft || !barrelRollRight)
				playerHealth -= 7;
		}
		if (blockFlag)
		{
			Obstacle block(blockX, blockY, 1);
			block.draw(0);
			if (ship.collideWithObstacle(block))
			{
				if (!barrelRollLeft || !barrelRollRight)
					playerHealth -= 5;
				blockFlag = 0;
				//t = 0;
			}
		}
		//energyUp

		if (energyUpFlag)
		{
			PowerUp energyUp(energyUpX, energyUpY, 1);
			energyUp.draw(1);
			if (ship.collideWithPowerUp(energyUp))
			{
				//cout << "Upgrade Time!\n";
				score += 2;
				energyUpFlag = 0;
				energyUpY = height - 100;
				playerHealth += 5;


			}
		}


		if (powerUpFlag)
		{
			PowerUp powerUp(powerUpX, powerUpY, 1);
			powerUp.draw(0);
			if (ship.collideWithPowerUp(powerUp))
			{
				//cout << "Upgrade Time!\n";
				score += 2;
				powerUpFlag = 0;
				powerUpY = height - 100;
				if (frame1 < 3)
				{
					frame1++;
				}

			}
		}

		if (spaceFlag)
		{

			//PlaySound(TEXT("laserSoundEffect.wav"), NULL, SND_ASYNC | SND_FILENAME );
			int dmg = 10;
			if (frame1 == 1)
			{
				Obstacle laser(laserX[0], laserY[0], frame1);
				laser.draw(1);

				if (boss.collideWithObstacle(laser))
				{
					bossHealth -= dmg;
					frameDmgFrame = 1;
					dmgCounterDeath = 25;
					dmgCounter = 1;
					score += 5;
					spaceFlag = 0;
				}
				//defender1
				if (defender1.collideWithObstacle(laser) || defender2.collideWithObstacle(laser) || defender2.collideWithObstacle(laser))
				{
					//cout << "Hit The Enemy!\n";
					spaceFlag = 0;
				}
				if (laser.getYMax() > 750)
				{
					spaceFlag = 0;
				}
			}
			else
			{
				if (frame1 == 2)
				{
					Obstacle laser1(laserX[0], laserY[0], frame1);
					laser1.draw(1);
					Obstacle laser2(laserX[1], laserY[1], frame1);
					laser2.draw(1);
					if (boss.collideWithObstacle(laser1))
					{
						bossHealth -= dmg * 2;
						frameDmgFrame = 1;
						dmgCounter = 1;
						score += 5;
						spaceFlag = 0;
					}
					if (defender1.collideWithObstacle(laser1) || defender2.collideWithObstacle(laser1) || defender2.collideWithObstacle(laser1))
					{
						//cout << "Hit The Enemy!\n";
						spaceFlag = 0;
					}
					if (boss.collideWithObstacle(laser2))
					{
						bossHealth -= dmg * 2;
						frameDmgFrame = 1;
						dmgCounterDeath = 25;
						dmgCounter = 1;
						score += 5;
						spaceFlag = 0;
					}
					if (defender1.collideWithObstacle(laser2) || defender2.collideWithObstacle(laser2) || defender2.collideWithObstacle(laser2))
					{
						//cout << "Hit The Enemy!\n";
						spaceFlag = 0;
					}
					if (laser1.getYMax() > 750 && laser2.getYMax() > 750)
					{
						spaceFlag = 0;
					}
				}
				else
				{
					if (frame1 == 3)
					{
						Obstacle laser1(laserX[0], laserY[0], frame1);
						laser1.draw(1);
						Obstacle laser2(laserX[2], laserY[2], frame1);
						laser2.draw(1);
						Obstacle laser3(laserX[3], laserY[3], frame1);
						laser3.draw(1);
						if (boss.collideWithObstacle(laser1))
						{
							bossHealth -= dmg * 3;
							frameDmgFrame = 1;
							dmgCounterDeath = 25;
							dmgCounter = 1;
							score += 5;
							spaceFlag = 0;
						}
						if (defender1.collideWithObstacle(laser1) || defender2.collideWithObstacle(laser1) || defender2.collideWithObstacle(laser1))
						{
							//cout << "Hit The Enemy!\n";
							spaceFlag = 0;
						}
						if (boss.collideWithObstacle(laser2))
						{
							bossHealth -= dmg * 3;
							frameDmgFrame = 1;
							dmgCounterDeath = 25;
							dmgCounter = 1;
							score += 5;
							spaceFlag = 0;
						}
						if (defender1.collideWithObstacle(laser2) || defender2.collideWithObstacle(laser2) || defender2.collideWithObstacle(laser2))
						{
							//cout << "Hit The Enemy!\n";
							spaceFlag = 0;
						}
						if (boss.collideWithObstacle(laser3))
						{
							bossHealth -= dmg * 3;
							frameDmgFrame = 1;
							dmgCounterDeath = 25;
							dmgCounter = 1;
							score += 5;
							spaceFlag = 0;
						}
						if (defender1.collideWithObstacle(laser3) || defender2.collideWithObstacle(laser3) || defender2.collideWithObstacle(laser3))
						{
							//cout << "Hit The Enemy!\n";
							spaceFlag = 0;
						}
						if (laser1.getYMax() > 750 && laser2.getYMax() > 750 && laser3.getYMax() > 750)
						{
							spaceFlag = 0;
						}
					}
				}
			}
		}
	}

	glPopMatrix();
	glFlush();
}


void key(unsigned char key, int x, int y)
{
	if (key == GLUT_KEY_ESCAPE)
	{
		exit(EXIT_SUCCESS);
	}
	if (gameState == 1)
	{
		if (key == 'w') {
			frame0 = 0;
			if (playerY1 < 480) {
				playerY1 += movement;
			}
			else {
				playerY1 = 0;
			}
		}
		if (key == 's') {
			frame0 = 0;
			if (playerY1 > 0)
			{
				playerY1 -= movement;


			}
			else
			{
				playerY1 = 480;
			}
		}
		if (key == 'd') {
			frame0 = 1;
			if (playerX1 < width - 150)
			{
				playerX1 += movement;

			}
			else
			{
				playerX1 = 0;
			}
		}
		if (key == 'a') {
			frame0 = 2;
			if (playerX1 > 0)
			{

				playerX1 -= movement;

			}
			else
			{
				playerX1 = 1020;
			}
		}
		//
		if (key == 'l') {
			frame0 = 1;
			if (playerY1 < 480) {
				playerY1 += movement;
			}
			else {
				playerY1 = 0;
			}
			if (playerX1 < 1020) {
				playerX1 += movement;
			}
			else {
				playerX1 = 0;
			}
		}
		if (key == 'k') {
			frame0 = 1;
			if (playerY1 >0) {
				playerY1 -= movement;
			}
			else {
				playerY1 = 480;
			}
			if (playerX1 < 1020) {
				playerX1 += movement;
			}
			else {
				playerX1 = 0;
			}
		}
		if (key == 'i') {
			frame0 = 2;
			if (playerY1 < 480) {
				playerY1 += movement;
			}
			else {
				playerY1 = 0;
			}
			if (playerX1 >0) {
				playerX1 -= movement;
			}
			else {
				playerX1 = 1020;
			}
		}
		if (key == 'j') {
			frame0 = 2;
			if (playerY1 > 0) {
				playerY1 -= movement;
			}
			else {
				playerY1 = 480;
			}
			if (playerX1 >0) {
				playerX1 -= movement;
			}
			else {
				playerX1 = 1020;
			}
		}
		//
		if (key == ' ')
		{
			if (gameState == 1) {
				if (frame1 == 1)
				{
					laserX[0] = playerX1 + 72;
					laserY[0] = playerY1 + 150;
				}
				if (frame1 == 2)
				{
					laserX[0] = playerX1 + 52;
					laserY[0] = playerY1 + 150;
					laserX[1] = playerX1 + 102;
					laserY[1] = playerY1 + 150;
				}
				if (frame1 == 3)
				{
					laserX[0] = playerX1 + 72;
					laserY[0] = playerY1 + 150;
					laserX[2] = playerX1 + 72;
					laserY[2] = playerY1 + 150;
					laserX[3] = playerX1 + 72;
					laserY[3] = playerY1 + 150;
				}
				spaceFlag = 1;

			}
		}

		if (key == 'e')
		{
			barrelRollRight = 1;
		}
		if (key == 'q') {
			barrelRollLeft = 1;
		}
		glutPostRedisplay();
	}
	else {
		if (gameState == 0)
		{
			if (key)
			{
				gameState = 1;
			}

		}
		else
		{
			if (gameState == 2)
			{
				if (key == 'b')
				{
					gameState = 1;
				}
			}
		}
	}
	glutPostRedisplay();
}
float constant[2] = { 0.01,0.01 };
int counterBoss = 500;

void bezierTimer(int val)
{
	val++;
	glutPostRedisplay();
	if (val == 30) {
		val = 0;
	}
	p0[0][0] = 52;
	p0[0][1] = 127;
	p1[0][0] = 494;
	p1[0][1] = 7;
	p2[0][0] = 167;
	p2[0][1] = 437;
	p3[0][0] = 608;
	p3[0][1] = 286;
	if (movingBlock)
	{
		p0[0][0] = 52;
		p0[0][1] = 127;
		p1[0][0] = 494;
		p1[0][1] = 7;
		p2[0][0] = 167;
		p2[0][1] = 437;
		p3[0][0] = 608;
		p3[0][1] = 286;
		if (blockX > width)
		{
			constant[0] = -1 * constant[0];
		}
		if (blockX < 0)
		{
			constant[0] = -1 * constant[0];
		}
		if (blockY > width)
		{
			constant[0] = -1 * constant[0];
		}
		if (blockY < 0)
		{
			constant[0] = -1 * constant[0];
		}
		t[0] += constant[0];
	}
	//if (movingBlock)
	//{
	if (gameState == 1)
	{
		if (dmgCounter > 0)
			dmgCounter++;

		if (dmgCounter > dmgCounterDeath)
		{
			frameDmgFrame = 0;
			dmgCounter = 0;
		}
		if (counterBoss == 500)
		{

			counterBoss = 0;
			/*p0[1][0] = RandomNumber(37, 50);// 37;
			p0[1][1] = RandomNumber(485, 616);// 516;
			p1[1][0] = RandomNumber(103, 300);//103;
			p1[1][1] = RandomNumber(106, 200);//516;
			p2[1][0] = RandomNumber(484, 580);// 484;
			p2[1][1] = RandomNumber(210, 320);// 437;
			p3[1][0] = RandomNumber(538, 640);// 698;
			p3[1][1] = RandomNumber(383, 530);//429;*/
			int randomNumber = (int) RandomNumber(0, 4);
			//cout << randomNumber << "\n";
			//randomNumber = 3;
			if (randomNumber == 0)
			{
				p0[1][0] = 37;
				p0[1][1] = 516;
				p1[1][0] = 103;
				p1[1][1] = 516;
				p2[1][0] = 484;
				p2[1][1] = 437;
				p3[1][0] = 698;
				p3[1][1] = 429;
			}
			else
			{
				if (randomNumber == 1)
				{
					p0[1][0] = 100;
					p0[1][1] = 350;
					p1[1][0] = 200;
					p1[1][1] = 250;
					p2[1][0] = 600;
					p2[1][1] = 450;
					p3[1][0] = 550;
					p3[1][1] = 520;
				}
				else
				{
					if (randomNumber == 2)
					{
						p0[1][0] = 92;
						p0[1][1] = 400;
						p1[1][0] = 220;
						p1[1][1] = 430;
						p2[1][0] = 490;
						p2[1][1] = 210;
						p3[1][0] = 490;
						p3[1][1] = 430;
					}
					else {
						if (randomNumber == 3)
						{
							p0[1][0] = 92;
							p0[1][1] = 300;
							p1[1][0] = 264;
							p1[1][1] = 106;
							p2[1][0] = 562;
							p2[1][1] = 410;
							p3[1][0] = 667;
							p3[1][1] = 383;
						}
					}
				}
			}
		}
		counterBoss++;
		if (bossX > width)
		{
			constant[1] = -1 * constant[1];
		}
		if (bossX < 0)
		{
			constant[1] = -1 * constant[1];
		}
		if (bossY > 550)
		{
			constant[1] = -1 * constant[1];
		}
		if (bossY < 50)
		{
			constant[1] = -1 * constant[1];
		}
		t[1] += constant[1];
	}
	//}
	glutTimerFunc(15, bezierTimer, val);

}

void timer(int val)
{

	if (barrelRollRight)
	{
		val++;
		glutPostRedisplay();
		if (val == 1) {
			frame0 = 1;
			if (playerX1 < 1020)
			{
				playerX1 += movement / 2;
			}
			else
			{
				playerX1 = 0;
			}
		}
		if (val == 10)
		{
			frame0 = 3;
			if (playerX1 < 1020)
			{
				playerX1 += movement / 2;
			}
			else
			{
				playerX1 = 0;
			}
		}
		if (val == 30)
		{
			frame0 = 2;
			if (playerX1 < 1020)
			{
				playerX1 += movement / 2;
			}
			else
			{
				playerX1 = 0;
			}
		}
		if (val == 50)
		{
			val = 0;

			frame0 = 0;
			if (playerX1 < 1020)
			{
				playerX1 += movement / 2;
			}
			else
			{
				playerX1 = 0;
			}
			barrelRollRight = 0;

		}
	}
	if (barrelRollLeft) {
		val++;
		glutPostRedisplay();
		if (val == 1) {
			frame0 = 2;
			if (playerX1 > 0)
			{
				playerX1 -= movement / 2;
			}
			else
			{
				playerX1 = 1020;
			}
		}
		if (val == 10)
		{
			frame0 = 3;
			if (playerX1 > 0)
			{
				playerX1 -= movement / 2;
			}
			else
			{
				playerX1 = 1020;
			}
		}
		if (val == 30)
		{
			frame0 = 1;
			if (playerX1 > 0)
			{
				playerX1 -= movement / 2;
			}
			else
			{
				playerX1 = 1020;
			}
		}
		if (val == 50)
		{
			val = 0;

			frame0 = 0;
			if (playerX1 > 0)
			{
				playerX1 -= movement / 2;
			}
			else
			{
				playerX1 = 1020;
			}
			barrelRollLeft = 0;

		}
	}
	glutTimerFunc(7, timer, val);
}
void laserTimer(int val)
{
	val++;
	glutPostRedisplay();
	if (val == 30) {
		val = 0;
	}
	if (spaceFlag) {
		if (frame1 == 1 || frame1 == 2)
		{
			laserY[0] += movement;
			laserY[1] += movement;
		}
		if (frame1 == 3)
		{
			laserY[0] += movement;
			laserY[2] += movement;
			laserY[3] += movement;
			laserX[2] -= movement;
			laserX[3] += movement;
		}
	}
	glutTimerFunc(15, laserTimer, val);
}
int main(int argc, char** argv)
{
	PlaySound(TEXT("SupernaturalHaste.wav"), NULL, SND_ASYNC | SND_LOOP);
	glutInit(&argc, argv);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Game On!");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(key);
	glutTimerFunc(0, timer, 0);
	glutTimerFunc(0, bezierTimer, 0);
	glutTimerFunc(0, laserTimer, 0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glClearColor(0, 0, 0, 0.0f);
	gluOrtho2D(0, width, 0, height);
	glutMainLoop();
}
