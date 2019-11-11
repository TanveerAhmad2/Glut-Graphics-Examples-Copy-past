#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MATRIXMAX 512
#define MAX_POINTS 10

typedef struct stVec{
	float x;
	float y;
	float z;
} Vector;

void setcontrolPointsPoint(int index, int dX, int dY);
void processMouse(int button, int state, int x, int y);
void processMousePassiveMotion(int x, int y);
void display(void);
void reshape(int w, int h);
void addcontrolPointsPoint(int dX, int dY);
void processKeys(unsigned char key, int x, int y);

int RESOLUTION = 2000;
int n, ORDER = 0;
int width = 700, height = 450;

float t;
float bezierArray[MAX_POINTS];

bool drawing = true;

Vector vMatrix [MATRIXMAX][MATRIXMAX];
Vector controlPoints [MAX_POINTS];
Vector stringart [MAX_POINTS][MAX_POINTS];

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Decasteljeau Bezier test");
  glutDisplayFunc(display);
	gluOrtho2D(0,width,0,height);

    //glutReshapeFunc(reshape);

    glutMouseFunc(processMouse);
    glutPassiveMotionFunc(processMousePassiveMotion);
	glutKeyboardFunc(processKeys);

	printf("Use \'+\' and \'-\' to increase/decrease scale\n");
	printf("Use left mouse to start/plot control points\n");
	printf("Use right mouse to remove newest control point\n");
	printf("Use spacebar/middle mouse to toggle \'elastic\' mode.\n\n");

	glutMainLoop();

    return 0;
}

// reshapes window to keep proportions
void reshape(int nw, int nh)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (nw <= nh)
		gluOrtho2D(-10.0, 10.0, -10.0 * (float) nh/nw, 10.0 * (float)nh/nw);
	else
		gluOrtho2D(-10.0 * (float)nw/nh, 10.0 * (float)nw / nh, -10.0, 10.0);

	glViewport(0,0,nw, nh);

	width = nw;
	height = nh;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glFlush();
	return;
}

// draws the display window and curve
void display(void){
    int i,j;
    int k;
    Vector bezier;

    k = ORDER;

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();

    //size and colour of controlPoints points
    glColor3f(0,1,0);
    glPointSize(4.0);

    //plot controlPoints points
    for( i = 0; i < ORDER; i++ ){
        glBegin(GL_POINTS);
        glVertex3f(controlPoints[i].x, controlPoints[i].y, controlPoints[i].z);
        glEnd();
    }

	// fill top row with controlPoints points
    for(i=0; i < ORDER + 1; i++){
        stringart[0][i] = controlPoints[i];
    }

    //size and colour of curve plots
    glColor3f(1,0,0);
    glPointSize(1.0);

    //plot curve
    for( t = 0; t < RESOLUTION; t++ ){
        glBegin(GL_POINTS);
        double scale = (double)t / RESOLUTION;

        //decasteljeau calculation
        for (i = 1; i < (k+1); i++){
            for (j = 0; j < (k+1-i); j++){
                stringart[i][j].x = (float)((1-scale) * stringart[i-1][j].x) + (float)(scale * stringart[i-1][j+1].x);
                stringart[i][j].y = (float)((1-scale) * stringart[i-1][j].y) + (float)(scale * stringart[i-1][j+1].y);
                stringart[i][j].z = (float)((1-scale) * stringart[i-1][j].z) + (float)(scale * stringart[i-1][j+1].z);
            }
        }

    bezier.x = stringart[k][0].x;
    bezier.y = stringart[k][0].y;
    bezier.z = stringart[k][0].z;

    glVertex3f(bezier.x, bezier.y, 0);
        glEnd();
    }
    glFlush();
	return;
}

void processMouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        if(ORDER < MAX_POINTS) addcontrolPointsPoint(x,y);
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_UP){
		if(ORDER > 0) ORDER--;
    }
	if(button == GLUT_MIDDLE_BUTTON && state == GLUT_UP){
		drawing = !drawing;
	}
}

void addcontrolPointsPoint(int dX, int dY){
	if(ORDER > MAX_POINTS)	return;

	ORDER++;
    controlPoints[ORDER].x=(float) dX;
    controlPoints[ORDER].y=(float) height - dY;
    controlPoints[ORDER].z=(float) 0;
    display();
}

void processMousePassiveMotion(int x, int y) {
	if(!drawing) return;
	if(ORDER >= MAX_POINTS) return;

	controlPoints[ORDER].x=(float) x;
    controlPoints[ORDER].y=(float) height - y;
    controlPoints[ORDER].z=(float) 0;

	display();
}

void processKeys(unsigned char key, int x, int y){
	if(key == 27) exit(0);
	if(key == 32) drawing = !drawing;
	if(key == 43 && RESOLUTION < 10000){
		RESOLUTION += 100;
		printf("Increasing resolution (scale) to %d (max=10000, min=100)\n", RESOLUTION);
	}
	if(key == 45 && RESOLUTION > 100){
		RESOLUTION -= 100;
		printf("Decreasing resolution (scale) to %d (max=10000, min=100)\n", RESOLUTION);
	}
	display();
}
