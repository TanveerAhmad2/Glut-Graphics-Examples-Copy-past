#include<windows.h>
#include<GL/freeglut.h>
#include<time.h>
#include<stdio.h>


#define dx 15
#define dy 25

#define TITLE 0
#define MENU 1
#define MEMALLOC 2
#define FRAGMENT 3

void *currentfont;

GLint i, j, k;
GLsizei w = 1366, h = 768;

int flag = 0, memIndex = 0, once = 0;

typedef struct AddressBlock
{
	int size[20];
	int addr[20];
	int count;
	int blocksize;
}AddressBlock;

typedef struct MemoryBlock
{
	int sizeValues[20];
	int xdValues[20];
	int allocated[20];
	int count;
}MemoryBlock;


//GENERAL FUNCTIONS
void drawPlayer(GLint x, GLint y);
void drawstring(float x, float y, char *string);
void genBox(GLint x, GLint y, int count, int sizeValues[20]);
int genRandomBox(GLint x, GLint y, int xdValues[20], int sizeValues[20]);
void box(GLint x, GLint y, int xd, int yd);
void drawCheckMark(int x, int y);
void drawCrossMark(int x, int y);
void drawBox(GLint x, GLint y, int size);
void animateFragments(int);
void fragmentation();
/****************FRagmentation**********/

class Fragment
{
public:
	static MemoryBlock MemBlock;
	static AddressBlock AddrBlock;
	//static int positions[5];
	static bool ExternalFragmentation;

	Fragment();
	static void drawMemBlocks();
	static void initializeAddrBlocks();
	static void drawAddressBlock();
	static void allocateFragments(int);
	static void drawAllocBox();
};

bool Fragment::ExternalFragmentation = true;

AddressBlock Fragment::AddrBlock;
MemoryBlock Fragment::MemBlock;
//bool BestFit::playanim = false;
//int BestFit::ychange = 0;
//int BestFit::xchange = 0;
//int BestFit::positions[5] = { 270, h - 150, h - 230, h - 118, h - 239 };

Fragment::Fragment()
{
	int temp, count = 0, xd = 300;
	srand(time(NULL));
	for (i = 0; i < 3 && (xd<1000); i++)
	{
		temp = rand() % 200;
		while ((temp>30) && (xd<1000))
		{
			MemBlock.xdValues[count] = xd;
			MemBlock.sizeValues[count] = temp;
			count++;
			xd = xd + temp + 5;
			temp = rand() % 120;
		}
	}
	MemBlock.count = count;
	initializeAddrBlocks();
	printf("asda");
}

void Fragment::allocateFragments(int memIndex)
{
	int i, small[2];
	for (i = 0; i <AddrBlock.count; i++)
	{
		if ((AddrBlock.size[i] >= MemBlock.sizeValues[memIndex]) && (MemBlock.allocated[memIndex] != -2))
		{
			small[0] = AddrBlock.size[i];
			small[1] = AddrBlock.addr[i];
			break;
		}
	}
	if (i == AddrBlock.count)
	{
		MemBlock.allocated[memIndex] = -2;
		return;
	}

	for (; i < AddrBlock.count; i++)
	{
		if ((AddrBlock.size[i] < small[0]) && (AddrBlock.size[i] >= MemBlock.sizeValues[memIndex]))
		{
			small[0] = AddrBlock.size[i];
			small[1] = AddrBlock.addr[i];
		}
	}

	for (i = 0; i < AddrBlock.count; i++)
	{
		if (small[0] == AddrBlock.size[i])
		{
			if (AddrBlock.size[i] != 0)
			{
				glColor3f(1, 1, 1);
				drawstring((AddrBlock.size[i] / 2) + AddrBlock.addr[i], h - 570, "EF");
				glBegin(GL_LINES);
				glVertex2i((AddrBlock.size[i] / 2) + AddrBlock.addr[i], h - 560);
				glVertex2i((AddrBlock.size[i] / 2) + AddrBlock.addr[i], h - 532);
				glEnd();
			}
			AddrBlock.size[i] -= MemBlock.sizeValues[memIndex];
			MemBlock.allocated[memIndex] = AddrBlock.addr[i];
			AddrBlock.addr[i] += MemBlock.sizeValues[memIndex];
			if (AddrBlock.size[i] != 0)
			{
				glColor3f(0, 0, 0);
				drawstring((AddrBlock.size[i] / 2) + AddrBlock.addr[i], h - 570, "EF");
				glBegin(GL_LINES);
				glVertex2i((AddrBlock.size[i] / 2) + AddrBlock.addr[i], h - 560);
				glVertex2i((AddrBlock.size[i] / 2) + AddrBlock.addr[i], h - 532);
				glEnd();
			}
			break;
		}
	}

}
void Fragment::initializeAddrBlocks()
{
	int temp, count = 0, xd = 300;
	srand(time(NULL));
	for (i = 0; i < 3 && (xd<1000); i++)
	{
		temp = rand() % 250;
		while ((temp>30) && (xd<1000))
		{
			AddrBlock.addr[count] = xd;
			AddrBlock.size[count] = temp;
			count++;
			xd = xd + temp;
			temp = rand() % 200;
		}
	}
	AddrBlock.count = count;
}
void Fragment::drawMemBlocks()
{
	char buffer[10] = "asd";
	glColor3i(0, 0, 0);
	for (int i = 0; i < MemBlock.count; i++)
	{
		box(MemBlock.xdValues[i], h - 300, MemBlock.sizeValues[i], 30);
		_itoa_s(MemBlock.sizeValues[i], buffer, sizeof(buffer), 10);
		drawstring(MemBlock.xdValues[i], h - 295, buffer);
	}
	glFlush();
}
void Fragment::drawAddressBlock()
{
	char buffer[10] = "asd";
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(AddrBlock.addr[0], h - 500);
	glVertex2i(AddrBlock.addr[AddrBlock.count - 1] + 1 + AddrBlock.size[AddrBlock.count - 1], h - 500);
	glVertex2i(AddrBlock.addr[AddrBlock.count - 1] + 1 + AddrBlock.size[AddrBlock.count - 1], h - 531);
	glVertex2i(AddrBlock.addr[0], h - 531);
	glEnd();
	for (int i = 0; i < AddrBlock.count; i++)
	{
		glColor3f(0, 0.9, 0);
		box(AddrBlock.addr[i], h - 500, AddrBlock.size[i], 30);
		_itoa_s(AddrBlock.size[i], buffer, sizeof(buffer), 10);
		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		glVertex2i(AddrBlock.addr[i], h - 500);
		glVertex2i(AddrBlock.addr[i], h - 530);
		glEnd();
		drawstring(AddrBlock.addr[i], h - 495, buffer);
	}
	glFlush();
}

/****************FRagmentation**********/

/****************BEST FIT***************/
class BestFit
{
public:
	static bool generated, playanim;
	static int ychange, xchange, positions[5];
	static MemoryBlock MemBlock;
	static AddressBlock AddrBlock;
public:
	BestFit();
	static void  animate();
	static void allocate();			//diff
	static void initializeAddrBlocks();	//same
	static void reInitializeMemBlocks();
	static void setAddrBlockSize(int size);	//same
};

bool BestFit::generated = false;
bool BestFit::playanim = false;
int BestFit::ychange = 0;
int BestFit::xchange = 0;
int BestFit::positions[5] = { 270, h - 150, h - 230, h - 118, h - 239 };

AddressBlock BestFit::AddrBlock;
MemoryBlock BestFit::MemBlock;

BestFit::BestFit()
{
	setAddrBlockSize(100);
}

void BestFit::reInitializeMemBlocks()
{
	for (int i = 0; i < MemBlock.count; i++)
		BestFit::MemBlock.allocated[i] = -1;
}

void BestFit::allocate()
{
	int i, small[2];
	for (int memIndex = 0; memIndex < MemBlock.count; memIndex++)
	{

		for (i = 0; i <AddrBlock.count; i++)
		{
			if ((AddrBlock.size[i] >= MemBlock.sizeValues[memIndex]) && (MemBlock.allocated[memIndex] != -2))
			{
				small[0] = AddrBlock.size[i];
				small[1] = AddrBlock.addr[i];
				break;
			}
		}
		if (i == AddrBlock.count)
		{
			MemBlock.allocated[memIndex] = -2;
			continue;
		}

		for (; i < AddrBlock.count; i++)
		{
			if ((AddrBlock.size[i] < small[0]) && (AddrBlock.size[i] >= MemBlock.sizeValues[memIndex]))
			{
				small[0] = AddrBlock.size[i];
				small[1] = AddrBlock.addr[i];
			}
		}

		for (i = 0; i < AddrBlock.count; i++)
		{
			if (small[0] == AddrBlock.size[i])
			{
				AddrBlock.size[i] -= MemBlock.sizeValues[memIndex];
				MemBlock.allocated[memIndex] = AddrBlock.addr[i];
				AddrBlock.addr[i] += MemBlock.sizeValues[memIndex];
				break;
			}
		}
	}
}

void BestFit::animate()
{
	static int index = 0;
	glPushMatrix();
	glColor3f(0, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(MemBlock.allocated[index], -ychange, 0);
	if (MemBlock.allocated[index] >= 0)
		box(MemBlock.xdValues[index], h - 150, MemBlock.sizeValues[index], 30);
	glPopMatrix();
	index++;
}

void BestFit::setAddrBlockSize(int size)
{
	AddrBlock.blocksize = size;
	AddrBlock.count = 1000 / AddrBlock.blocksize;
	initializeAddrBlocks();
}
void BestFit::initializeAddrBlocks()
{
	for (int i = 0; i <AddrBlock.count; i++)
	{
		AddrBlock.size[i] = AddrBlock.blocksize;
		AddrBlock.addr[i] = i*AddrBlock.blocksize;
	}
}
/****************BEST FIT***************/

/****************WORST FIT***************/
class WorstFit
{
public:
	static bool generated, playanim;
	static int ychange, xchange, positions[5];
	static MemoryBlock MemBlock;
	static AddressBlock AddrBlock;
public:
	WorstFit();
	static void  animate();
	static void allocate();			//diff
	static void initializeAddrBlocks();	//same
	static void reInitializeMemBlocks();
	static void setAddrBlockSize(int size);	//same
};

bool WorstFit::generated = false;
bool WorstFit::playanim = false;
int WorstFit::ychange = 0;
int WorstFit::xchange = 0;
int WorstFit::positions[5] = { 480, h - 360, h - 450, h - 332, h - 449 };

AddressBlock WorstFit::AddrBlock;
MemoryBlock WorstFit::MemBlock;

WorstFit::WorstFit()
{
	setAddrBlockSize(100);
}

void WorstFit::reInitializeMemBlocks()
{
	for (int i = 0; i < MemBlock.count; i++)
		WorstFit::MemBlock.allocated[i] = -1;
}

void WorstFit::allocate()
{
	int i, large[2];
	for (int memIndex = 0; memIndex < MemBlock.count; memIndex++)
	{

		for (i = 0; i < AddrBlock.count; i++)
		{
			if ((AddrBlock.size[i] >= MemBlock.sizeValues[memIndex]) && (MemBlock.allocated[memIndex] != -2))
			{
				large[0] = AddrBlock.size[i];
				large[1] = AddrBlock.addr[i];
				break;
			}
		}
		if (i == AddrBlock.count)
		{
			MemBlock.allocated[memIndex] = -2;
			continue;
		}

		for (; i < AddrBlock.count; i++)
		{
			if ((AddrBlock.size[i] > large[0]) && (AddrBlock.size[i] >= MemBlock.sizeValues[memIndex]))
			{
				large[0] = AddrBlock.size[i];
				large[1] = AddrBlock.addr[i];
			}
		}

		for (i = 0; i < AddrBlock.count; i++)
		{
			if (large[0] == AddrBlock.size[i])
			{
				AddrBlock.size[i] -= MemBlock.sizeValues[memIndex];
				MemBlock.allocated[memIndex] = AddrBlock.addr[i];
				AddrBlock.addr[i] += MemBlock.sizeValues[memIndex];
				break;
			}
		}
	}
}

void WorstFit::animate()
{
	static int index = 0;
	glPushMatrix();
	glColor3f(0, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(MemBlock.allocated[index], -ychange, 0);
	if (MemBlock.allocated[index] >= 0)
		box(MemBlock.xdValues[index], h - 150, MemBlock.sizeValues[index], 30);
	glPopMatrix();
	index++;
}

void WorstFit::setAddrBlockSize(int size)
{
	AddrBlock.blocksize = size;
	AddrBlock.count = 1000 / AddrBlock.blocksize;
	initializeAddrBlocks();
}
void WorstFit::initializeAddrBlocks()
{
	for (int i = 0; i <AddrBlock.count; i++)
	{
		AddrBlock.size[i] = AddrBlock.blocksize;
		AddrBlock.addr[i] = i*AddrBlock.blocksize;
	}
}
/****************WORST FIT***************/

/****************FIRST FIT***************/
class FirstFit
{
public:
	static bool generated, playanim;
	static int ychange, xchange, positions[5];
	static MemoryBlock MemBlock;
	static AddressBlock AddrBlock;
public:
	FirstFit();
	static void  animate();
	static void allocate();			//diff
	static void initializeAddrBlocks();	//same
	static void reInitializeMemBlocks();
	static void setAddrBlockSize(int size);	//same
};

bool FirstFit::generated = false;
bool FirstFit::playanim = false;
int FirstFit::ychange = 0;
int FirstFit::xchange = 0;
int FirstFit::positions[5] = { 710, h - 590, h - 680, h - 560, h - 680 };

AddressBlock FirstFit::AddrBlock;
MemoryBlock FirstFit::MemBlock;

FirstFit::FirstFit()
{
	setAddrBlockSize(100);
}

void FirstFit::reInitializeMemBlocks()
{
	for (int i = 0; i < MemBlock.count; i++)
		FirstFit::MemBlock.allocated[i] = -1;
}

void FirstFit::allocate()
{
	int i, small[2];
	for (int memIndex = 0; memIndex < MemBlock.count; memIndex++)
	{

		for (i = 0; i <AddrBlock.count; i++)
		{
			if ((AddrBlock.size[i] >= MemBlock.sizeValues[memIndex]) && (MemBlock.allocated[memIndex] != -2))
			{
				small[0] = AddrBlock.size[i];
				small[1] = AddrBlock.addr[i];
				break;
			}
		}
		if (i == AddrBlock.count)
		{
			MemBlock.allocated[memIndex] = -2;
			continue;
		}
		/*
		for (; i < AddrBlock.count; i++)
		{
		if ((AddrBlock.size[i] < small[0]) && (AddrBlock.size[i] >= MemBlock.sizeValues[memIndex]))
		{
		small[0] = AddrBlock.size[i];
		small[1] = AddrBlock.addr[i];
		}
		}*/

		for (i = 0; i < AddrBlock.count; i++)
		{
			if (small[0] == AddrBlock.size[i])
			{
				AddrBlock.size[i] -= MemBlock.sizeValues[memIndex];
				MemBlock.allocated[memIndex] = AddrBlock.addr[i];
				AddrBlock.addr[i] += MemBlock.sizeValues[memIndex];
				break;
			}
		}
	}
}

void FirstFit::animate()
{
	static int index = 0;
	glPushMatrix();
	glColor3f(0, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(MemBlock.allocated[index], -ychange, 0);
	if (MemBlock.allocated[index] >= 0)
		box(MemBlock.xdValues[index], h - 150, MemBlock.sizeValues[index], 30);
	glPopMatrix();
	index++;
}

void FirstFit::setAddrBlockSize(int size)
{
	AddrBlock.blocksize = size;
	AddrBlock.count = 1000 / AddrBlock.blocksize;
	initializeAddrBlocks();
}
void FirstFit::initializeAddrBlocks()
{
	for (int i = 0; i <AddrBlock.count; i++)
	{
		AddrBlock.size[i] = AddrBlock.blocksize;
		AddrBlock.addr[i] = i*AddrBlock.blocksize;
	}
}
/****************FIRST FIT***************/
template <typename classType>
void redraw(classType b)
{
	glColor3f(0, 0, 0);
	drawAddressBlocks(b, b.positions[0]);
	if (b.playanim == false)
		genBox(295, b.positions[1], b.MemBlock.count, b.MemBlock.sizeValues);
	else
	{
		genAllocBox(b);
	}
	drawPlayer(64, b.positions[2]);
	printf("%d\n", b.playanim);
	glFlush();
}

template <typename classType>
void genAllocBox(classType b)
{
	genBox(295, b.positions[1], b.MemBlock.count, b.MemBlock.sizeValues);
	for (int i = 0; i<b.MemBlock.count; i++)
	{

		if (b.MemBlock.allocated[i] >= 0)
		{
			drawCheckMark(b.MemBlock.xdValues[i], b.positions[3]);
			glColor3f(0.9, 0, 0);
			box(b.MemBlock.allocated[i] + 295, b.positions[4], b.MemBlock.sizeValues[i], 30);
			glColor3f(0, 0, 0);
			Sleep(800);
		}
		else
			drawCrossMark(b.MemBlock.xdValues[i] + 8, b.positions[3]);
	}
	AddressBlockRedisplay(b, b.positions[0]);
	glColor3f(0, 0, 0);
}

template <typename classType>
void drawAddressBlocks(classType b, int y)
{
	char buffer[10] = "blah";
	glColor3f(0, 0.9, 0);
	//glRecti(295, h-y, 1230,h- y1);
	glBegin(GL_POLYGON);
	glVertex2i(295, h - y);
	glVertex2i(1295, h - y);
	glVertex2i(1295, h - y + 30);
	glVertex2i(295, h - y + 30);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(295, h - y);
	glVertex2i(1295, h - y);
	glVertex2i(1295, h - y + 30);
	glVertex2i(295, h - y + 30);
	glEnd();
	for (int i = 0; i<b.AddrBlock.count; i++)
	{
		if (b.AddrBlock.size[i] == 0)
			continue;
		glBegin(GL_LINES);
		glVertex2i(295 + b.AddrBlock.addr[i], h - y);
		glVertex2i(295 + b.AddrBlock.addr[i], h - y + 30);
		glEnd();
		_itoa_s(b.AddrBlock.size[i], buffer, sizeof(buffer), 10);
		drawstring(287 + b.AddrBlock.addr[i] + 3, h - y - 12, buffer);
	}
	glFlush();
}

template <typename classType>
void randomize(classType b)
{
	b.playanim = false;
	glColor3f(0, 0, 0);
	for (i = 0; i < b.MemBlock.count; i++)
		b.MemBlock.allocated[i] = -1;
	b.MemBlock.count = genRandomBox(295, b.positions[1], b.MemBlock.xdValues, b.MemBlock.sizeValues);
	b.initializeAddrBlocks();
	drawAddressBlocks(b, b.positions[0]);
	drawPlayer(64, b.positions[2]);
	b.generated = true;
	glFlush();
	//printf("randomize called\n");
}


template <typename classType>
void AddressBlockRedisplay(classType b, int y)
{
	char buffer[10] = "blah";
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(295, h - y);
	glVertex2i(1295, h - y);
	glVertex2i(1295, h - y + 30);
	glVertex2i(295, h - y + 30);
	glEnd();
	for (int i = 0; i<b.AddrBlock.count; i++)
	{
		glColor3f(0, 0, 0);
		if (b.AddrBlock.size[i] == 0)
			continue;
		glBegin(GL_LINES);
		glVertex2i(295 + b.AddrBlock.addr[i], h - y);
		glVertex2i(295 + b.AddrBlock.addr[i], h - y + 30);
		glEnd();
		_itoa_s(b.AddrBlock.size[i], buffer, sizeof(buffer), 10);
		drawstring(287 + b.AddrBlock.addr[i] + 3, h - y - 12, buffer);
	}
	glFlush();

}

void setFont(void *font)
{
	currentfont = font;
}



void drawstring(float x, float y, char *string)
{
	char *c;
	if (x < 0)		//middle of the screen
		x = (w / 2) - (strlen(string) * 7);
	glRasterPos3f(x, y, 1.0);
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(currentfont, *c);
	}
}



void myInit()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(5.0);
	gluOrtho2D(0.0, w, 0.0, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);

}


void box(GLint x, GLint y, int xd, int yd)
{
	glBegin(GL_POLYGON);
	glVertex2d(x, y);
	glVertex2d(x + xd, y);
	glVertex2d(x + xd, y - yd);
	glVertex2d(x, y - yd);
	glEnd();
	glFlush();
}

void genBox(GLint x, GLint y, int count, int sizeValues[20])
{
	char buffer[10] = "asd";
	for (i = 0; i<count; i++)
	{
		if (sizeValues[i] == -1)
			continue;
		box(x, y, sizeValues[i], 30);
		_itoa_s(sizeValues[i], buffer, sizeof(buffer), 10);
		drawstring(x, y + 10, buffer);
		x = x + sizeValues[i] + 5;
	}
}

void genBox(GLint x, GLint y, int count, int sizeValues[20], bool gap)
{
	char buffer[10] = "asd";
	for (i = 0; i<count; i++)
	{
		if (sizeValues[i] == -1)
			continue;
		box(x, y, sizeValues[i], 30);
		_itoa_s(sizeValues[i], buffer, sizeof(buffer), 10);
		drawstring(x, y + 10, buffer);
		if (gap == true)
			x = x + sizeValues[i] + 5;
		else
			x = x + sizeValues[i];
	}
}


int genRandomBox(GLint x, GLint y, int xdValues[20], int sizeValues[20])
{
	int temp, xd = x, count = 0;
	char buffer[10] = "asd";
	glColor3i(0, 0, 0);
	for (i = 0; i < 3 && (xd<1200); i++)
	{
		temp = rand() % 200;
		while ((temp>30) && (xd<1200))
		{
			xdValues[count] = xd;
			sizeValues[count] = temp;
			//printf("tempV=%d xdV=%d\n", sizeValues[count], xdValues[count]);
			count++;
			box(xd, y, temp, 30);
			_itoa_s(temp, buffer, sizeof(buffer), 10);
			drawstring(xd, y + 10, buffer);
			xd = xd + temp + 5;
			temp = rand() % 120;
		}
	}/*
	 for (i = 0; i < count; i++)
	 WorstFit::MemBlock.allocated[i] = -1;*/
	return count;
}

void handleBestFit(BestFit b)
{
	glColor3f(0, 0, 0);
	drawstring(295, h - 205, "Select Block Size :");
	drawstring(156, h - 168, "Memory Blocks");
	drawstring(156, h - 250, "Memory Space");
	drawstring(65, h - 140, "BESTFIT");
	glColor3f(0.9, 0.9, 0);
	box(410, h - 190, 50, 20);
	box(470, h - 190, 50, 20);
	glColor3f(0, 0, 0);
	setFont(GLUT_BITMAP_HELVETICA_12);
	drawstring(425, h - 205, "100");
	drawstring(485, h - 205, "200");

	if (BestFit::generated == false)
		randomize(b);
	else
		//WorstFit::redraw();
		redraw(b);
}

void handleWorstFit(WorstFit w)
{
	glColor3f(0, 0, 0);
	drawstring(65, h - 350, "WORSTFIT");
	drawstring(295, h - 416, "Select Block Size :");
	drawstring(156, h - 378, "Memory Blocks");
	drawstring(156, h - 465, "Memory Space");

	glColor3f(0.9, 0.9, 0);
	box(410, h - 400, 50, 20);
	box(470, h - 400, 50, 20);
	glColor3f(0, 0, 0);
	setFont(GLUT_BITMAP_HELVETICA_12);
	drawstring(425, h - 415, "100");
	drawstring(485, h - 415, "200");

	if (WorstFit::generated == false)
		randomize(w);
	else
		//WorstFit::redraw();
		redraw(w);
}

void handleFirstFit(FirstFit f)
{
	glColor3f(0, 0, 0);
	drawstring(65, h - 580, "FIRSTFIT");
	drawstring(295, h - 646, "Select Block Size :");
	drawstring(156, h - 610, "Memory Blocks");
	drawstring(156, h - 695, "Memory Space");

	glColor3f(0.9, 0.9, 0);
	box(410, h - 630, 50, 20);
	box(470, h - 630, 50, 20);
	glColor3f(0, 0, 0);
	setFont(GLUT_BITMAP_HELVETICA_12);
	drawstring(425, h - 645, "100");
	drawstring(485, h - 645, "200");

	if (FirstFit::generated == false)
		randomize(f);
	else
		//WorstFit::redraw();
		redraw(f);
}

void drawMenuBox(GLint x, GLint y, char * str, int size)
{
	int xd, yd;
	glColor3f(0, 0.8, 1.0);
	if (size == 0)
	{
		xd = 70;
		yd = 30;
	}
	if (size == 1)
	{
		xd = 150;
		yd = 50;
	}
	if (size == 2)
	{
		xd = 350;
		yd = 50;
	}
	if (size == 3)
	{
		glColor3f(1, 1, 1);
		xd = w - 60;
		yd = 210;
	}
	box(x, y, xd, yd);
	glFlush();
	glColor3f(1, 1, 1);
	float temp = strlen(str);
	drawstring(x + (xd / 2) - (temp*4.5), y - (yd / 2) - 5, str);
	glFlush();

}

void drawBox(GLint x, GLint y, int size)
{
	int xd, yd;
	if (size == 0)
	{
		xd = 70;
		yd = 30;
	}
	if (size == 1)
	{
		xd = 150;
		yd = 50;
	}
	if (size == 2)
	{
		xd = 350;
		yd = 50;
	}
	if (size == 3)
	{
		glColor3f(1, 1, 1);
		xd = w - 60;
		yd = 210;
	}
	box(x, y, xd, yd);
	glFlush();

}
void border()
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(5, 5);
	glVertex2f(5, h - 5);
	glVertex2f(w - 5, h - 5);
	glVertex2f(w - 5, 5);
	glEnd();
}
void drawCheckMark(int x, int y)
{
	glColor3f(0, 0.9, 0);
	glBegin(GL_LINES);
	glVertex2i(x, y);
	glVertex2i(x + 7, y - 10);
	glVertex2i(x + 7, y - 10);
	glVertex2i(x + 20, y + 10);
	glEnd();
	glFlush();
}
void drawCrossMark(int x, int y)
{
	glColor3f(0.9, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(x - 7, y + 7);
	glVertex2i(x + 7, y - 7);
	glVertex2i(x - 7, y - 7);
	glVertex2i(x + 7, y + 7);
	glEnd();
	glFlush();
	glColor3f(0, 0, 0);
}
void title()
{
	setFont(GLUT_BITMAP_TIMES_ROMAN_24);
	glColor3f(1.0, 1.0, 1.0);
	border();
	drawstring(-1, 700, "BASAVESHWAR ENGINEERING COLLEGE - VIDYAGIRI BAGALKOT");

	drawstring(-1, 650, ":MEMORY MANAGEMENT AND ITS ORGANIZATION:");

	drawstring(-1, 550, "GUIDE");
	drawstring(600, 510, "DR. S.V.SABOJI");

	drawstring(-1, 450, "PROJECT ASSOCIATES");

	setFont(GLUT_BITMAP_HELVETICA_18);
	drawstring(500, 410, "VINAYASRI");
	drawstring(750, 410, "2BA12CS092");

	drawstring(500, 370, "YASHWANT");
	drawstring(750, 370, "2BA12CS094");

	drawstring(500, 330, "GURUPAD");
	drawstring(750, 330, "2BA12CS096");
	drawMenuBox(600, 250, "BEGIN", 1);
	glFlush();
}

void backbt()
{
	glColor3f(0, 0.8, 1.0);
	glRecti(30, h - 30, 65, h - 65);

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(47.5, h - 35);
	glVertex2f(35, h - 47.5);
	glVertex2f(47.5, h - 60);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(35, h - 47.5);
	glVertex2f(60, h - 47.5);
	glEnd();
	glFlush();

}

void closebt()
{
	glColor3f(0, 0.8, 1.0);
	glRecti(w - 30, h - 30, w - 65, h - 65);

	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(w - 60, h - 35);
	glVertex2f(w - 35, h - 60);
	glVertex2f(w - 35, h - 35);
	glVertex2f(w - 60, h - 60);
	glEnd();
}

void drawline()
{
	glColor3f(0, 0.8, 1.0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(30, h - 78);
	glVertex2f(w - 30, h - 78);
	glEnd();
}
void menus()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	border();
	backbt();
	closebt();
	setFont(GLUT_BITMAP_HELVETICA_18);
	drawMenuBox(500, 500, "Memory Allocation", 2);
	drawMenuBox(500, 440, "Fragmentaion Problem", 2);
	//drawMenuBox(500, 380, "Paging : Solution to fragmenation", 2);
}

void drawPlayer(GLint x, GLint y)
{
	glColor3f(0, 0.8, 1);
	glBegin(GL_TRIANGLES);
	glVertex2d(x, y);
	glVertex2d(x, y - 30);
	glVertex2d(x + 30, y - 15);
	glEnd();

	glRecti(x + 40, y, x + 70, y - 30);
	glColor3f(1, 1, 1);
	setFont(GLUT_BITMAP_HELVETICA_18);
	drawstring(x + 49, y - 22, "R");
	setFont(GLUT_BITMAP_HELVETICA_12);
	glFlush();

}

void memAlloc()
{
	glClear(GL_COLOR_BUFFER_BIT);
	border();
	backbt();
	closebt();
	drawline();
	setFont(GLUT_BITMAP_HELVETICA_18);
	drawMenuBox(100, 745, "Memory Allocation", 2);
	glColor3f(0.9, 0, 0);
	drawBox(465, h - 32, 0);
	glColor3f(1, 1, 1);
	setFont(GLUT_BITMAP_HELVETICA_12);
	drawstring(540, 718, "Allocated");
	glColor3f(0, 0.9, 0);
	drawBox(614, h - 32, 0);
	glColor3f(1, 1, 1);
	drawstring(690, 718, "Free space");
	glColor3f(1, 1, 1);
	drawBox(30, 680, 3);
	drawBox(30, 460, 3);
	drawBox(30, 240, 3);
	//firstfit();
	//worstfit();
	static BestFit b;
	static WorstFit w;
	static FirstFit f;
	handleBestFit(b);
	handleWorstFit(w);
	handleFirstFit(f);
	glFlush();

}

void fragmentation()
{
	glClear(GL_COLOR_BUFFER_BIT);
	border();
	backbt();
	closebt();
	drawline();
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2i(30, h - 237);
	glVertex2i(w - 30, h - 237);
	glVertex2i(w - 30, h - 740);
	glVertex2i(30, h - 740);
	glEnd();
	setFont(GLUT_BITMAP_HELVETICA_18);
	drawMenuBox(100, 745, "Fragmentation Problem", 2);

	int x = 700, y = h - 610;
	glColor3f(0, 0.8, 1.0);
	glRecti(x + 40, y, x + 70, y - 30);
	glColor3f(1, 1, 1);
	setFont(GLUT_BITMAP_HELVETICA_18);
	drawstring(x + 49, y - 22, "R");
	glFlush();

	glColor3f(0.9, 0, 0);
	drawBox(465, h - 32, 0); //allocated
	glColor3f(0, 0.9, 0);
	drawBox(614, h - 32, 0);	//free space
	glColor3f(0.9, 0.5, 0);
	drawBox(764, h - 32, 0);		//space used
	glColor3f(1, 1, 1);
	setFont(GLUT_BITMAP_HELVETICA_12);
	drawstring(540, 718, "Allocated");
	drawstring(690, 718, "Free space");
	drawstring(840, 718, "Space Used");

	setFont(GLUT_BITMAP_HELVETICA_18);
	drawMenuBox(220, h - 160, "Internal Fragmentation(IF)", 2);
	drawMenuBox(787, h - 160, "External Fragmentation(EF)", 2);

	setFont(GLUT_BITMAP_HELVETICA_12);
	glColor3i(0, 0, 0);
	drawstring(115, h - 325, "Memory Blocks");
	drawstring(115, h - 520, "Address Blocks");
	Fragment f;
	Fragment::drawMemBlocks();
	Fragment::drawAddressBlock();

	setFont(GLUT_BITMAP_HELVETICA_18);
	drawMenuBox(300, h - 600, "Allocate Next Block", 2);
	setFont(GLUT_BITMAP_HELVETICA_12);
	//animateFragments(true);
	glFlush();
}

void animateFragments(int i)
{
	int ychange = h - 350, xchange = 0;
	while (ychange > h - 450)
	{
		glColor3f(1, 1, 1);
		box(Fragment::MemBlock.xdValues[i], ychange, Fragment::MemBlock.sizeValues[i], 30);
		ychange -= 10;
		glColor3f(0.9, 0, 0);
		box(Fragment::MemBlock.xdValues[i], ychange, Fragment::MemBlock.sizeValues[i], 30);
		Sleep(40);
	}
	while (xchange <(Fragment::MemBlock.allocated[i] - 300))
	{
		glColor3f(1, 1, 1);
		box(Fragment::MemBlock.xdValues[i] + xchange, ychange, Fragment::MemBlock.sizeValues[i], 30);
		//if (Fragment::MemBlock.xdValues[i] < (Fragment::MemBlock.allocated[i]))
		//	xchange -= 10;
		//else
		xchange += 10;
		glColor3f(0.9, 0, 0);
		box(Fragment::MemBlock.xdValues[i] + xchange, ychange, Fragment::MemBlock.sizeValues[i], 30);
		Sleep(40);
	}
	glColor3f(1, 1, 1);
	box(Fragment::MemBlock.xdValues[i] + xchange, ychange, Fragment::MemBlock.sizeValues[i], 30);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glLoadIdentity();
	if (flag == TITLE)
		title();
	if (flag == MENU)
		//glClear(GL_COLOR_BUFFER_BIT);
		menus();
	if (flag == MEMALLOC)
	{
		memAlloc();
		//if (BestFit::playanim == true)
		//BestFit::animate();
	}
	if (flag == FRAGMENT)
	{
		fragmentation();
	}
}




void myMouse(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		printf("%d %d\n", x, y);
		if ((x >= 600 && x <= 750) && (y >= 500 && y <= 550))		//Menus Screen
		{
			flag = MENU;
			glutPostRedisplay();
		}
		if ((x >= 1300 && x <= 1335) && (y >= 30 && y <= 65) && (flag != TITLE))	//Exit Button
		{
			exit(8);
		}
		if ((x >= 30 && x <= 65) && (y >= 30 && y <= 65))			//Back to Main Screen
		{
			if (flag == MENU)
				flag = TITLE;
			else
			{
				flag = MENU;
				memIndex = 0;
				once = 0;
			}
			glutPostRedisplay();
		}
		if ((x >= 500 && x <= 850) && (flag == MENU))
		{
			if (y >= 270 && y <= 318)
			{
				flag = MEMALLOC;
				BestFit::generated = false;
				WorstFit::generated = false;
				FirstFit::generated = false;
				glutPostRedisplay();
			}
			if (y >= 330 && y <= 380)
			{
				flag = FRAGMENT;
				glutPostRedisplay();
			}
		}
		if (flag == MEMALLOC)
		{
			if ((x >= 64 && x <= 90))
			{
				if ((y >= 230 && y < 260))
				{
					BestFit::allocate();
					BestFit::playanim = true;
					//BestFit::animate();
					glutPostRedisplay();//		Use this to randomize
				}
				if ((y >= 450 && y < 480))
				{
					WorstFit::allocate();
					WorstFit::playanim = true;
					//BestFit::animate();
					glutPostRedisplay();//		Use this to randomize
				}
				if ((y >= 680 && y < 710))
				{
					FirstFit::allocate();
					FirstFit::playanim = true;
					WorstFit::playanim = false;
					//BestFit::animate();
					glutPostRedisplay();//		Use this to randomize
				}

			}
			if ((x >= 103 && x <= 134))
			{
				if ((y >= 230 && y < 260))
				{
					BestFit::generated = false;
					BestFit::playanim = false;
					glutPostRedisplay();//		Use this to randomize
				}
				if ((y >= 450 && y < 480))
				{
					WorstFit::generated = false;
					WorstFit::playanim = false;
					glutPostRedisplay();//		Use this to randomize
				}
				if ((y >= 680 && y < 710))
				{
					FirstFit::generated = false;
					FirstFit::playanim = false;
					glutPostRedisplay();//		Use this to randomize
				}

			}
			if ((y >= 190) && (y <= 210))
			{
				BestFit::reInitializeMemBlocks();
				if (x >= 410 && x <= 460)
				{
					BestFit::setAddrBlockSize(100);
					glutPostRedisplay();
				}
				if ((x >= 470) && (x <= 520))
				{
					BestFit::setAddrBlockSize(200);
					glutPostRedisplay();
				}
			}
			if ((y >= 400) && (y <= 420))
			{
				WorstFit::reInitializeMemBlocks();
				if (x >= 410 && x <= 460)
				{
					WorstFit::setAddrBlockSize(100);
					glutPostRedisplay();
				}
				if ((x >= 470) && (x <= 520))
				{
					WorstFit::setAddrBlockSize(200);
					glutPostRedisplay();
				}
			}
			if ((y >= 630) && (y <= 650))
			{
				FirstFit::reInitializeMemBlocks();
				if (x >= 410 && x <= 460)
				{
					FirstFit::setAddrBlockSize(100);
					glutPostRedisplay();
				}
				if ((x >= 470) && (x <= 520))
				{
					FirstFit::setAddrBlockSize(200);
					glutPostRedisplay();
				}
			}

		}
		if (flag == FRAGMENT)
		{
			if ((x > 300 && x<650) && (y>600 && y < 650))
			{
				glColor3f(0.9, 0, 0);
				if ((Fragment::MemBlock.allocated[memIndex] >= 0) && (memIndex < Fragment::MemBlock.count))
				{
					Fragment::allocateFragments(memIndex);
					if (Fragment::MemBlock.allocated[memIndex] >= 0)
					{
						animateFragments(memIndex);
						glColor3f(0.9, 0, 0);
						box(Fragment::MemBlock.allocated[memIndex], h - 500, Fragment::MemBlock.sizeValues[memIndex], 30);
						if (once == 0)
						{
							glColor3f(0.9, 0.5, 0);
							srand(time(NULL));
							box(Fragment::MemBlock.allocated[memIndex], h - 500, Fragment::MemBlock.sizeValues[memIndex] - 20, 30);
							glFlush();
							drawstring((Fragment::MemBlock.sizeValues[memIndex] - 20 / 2) + Fragment::MemBlock.allocated[memIndex], h - 580, "IF");
							glBegin(GL_LINES);
							glVertex2i((Fragment::MemBlock.sizeValues[memIndex] - 20 / 2) + Fragment::MemBlock.allocated[memIndex], h - 570);
							glVertex2i((Fragment::MemBlock.sizeValues[memIndex] - 20 / 2) + Fragment::MemBlock.allocated[memIndex], h - 532);
							glEnd();
							once++;
						}
						drawCheckMark(Fragment::MemBlock.xdValues[memIndex], h - 272);
					}
					else
						drawCrossMark(Fragment::MemBlock.xdValues[memIndex], h - 272);
				}
				memIndex++;
				//animateFragments(true);
			}
			if ((x>740 && x < 770) && (y >= 610 && y <= 640))
			{
				memIndex = 0;
				once = 0;
				glutPostRedisplay();
			}
		}
	}
}

void idle()
{
	if ((flag == MEMALLOC) && (BestFit::playanim == true))
	{
		if (BestFit::ychange < 90)	//		xchange -- >AllocAddr
		{
			BestFit::ychange += 10;
			//glutPostRedisplay();
		}
		else
		{
			BestFit::playanim = false;
			BestFit::ychange = 0;
		}
	}
	//glutPostRedisplay();
	glFlush();
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(w, h);
	glutCreateWindow("MEMORY MANAGEMENT");
	glutDisplayFunc(display);
	glutMouseFunc(myMouse);
	glutIdleFunc(idle);
	myInit();
	glutMainLoop();
}
