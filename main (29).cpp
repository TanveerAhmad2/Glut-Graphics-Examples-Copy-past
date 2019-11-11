#include<windows.h>
#include<iostream>

using namespace std;

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

const int FIELD_WIDTH = 60;
const int FIELD_HEIGHT = 80;
const int CELL_SIZE = 10;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

struct Color{
    float r, g, b;
};
Color black, white;

bool needQuad = false;
int posxq = 0, posyq = 0;
float angle = 0.0;
int time = 0;

int **matrix, **buffer;

void drawQuad(int xpos, int ypos, int xsize, int ysize, Color color=black){
    glBegin(GL_QUADS);
        glColor3f(color.r, color.g, color.b);
        glVertex2i(xpos, ypos);
        glColor3f(color.r, color.g, color.b);
        glVertex2i(xpos + xsize, ypos);
        glColor3f(color.r, color.g, color.b);
        glVertex2i(xpos + xsize, ypos + ysize);
        glColor3f(color.r, color.g, color.b);
        glVertex2i(xpos, ypos + ysize);
    glEnd();
}

void nextTick(){
    pair<int, int> dirs[8];
    dirs[0] = make_pair(1, 0);
    dirs[1] = make_pair(1, 1);
    dirs[2] = make_pair(1, -1);
    dirs[3] = make_pair(-1, -1);
    dirs[4] = make_pair(-1, 1);
    dirs[5] = make_pair(-1, 0);
    dirs[6] = make_pair(0, 1);
    dirs[7] = make_pair(0, -1);

    for(int i = 0; i < FIELD_HEIGHT; i++){
        for(int j = 0; j < FIELD_WIDTH; j++){
            int neibsCount = 0;
            for(int dir = 0; dir < 9; dir++){
                int nextx = j + dirs[dir].first, nexty = i + dirs[dir].second;
                if(nextx < 0) nextx = FIELD_WIDTH - 1;
                if(nexty < 0) nexty = FIELD_HEIGHT - 1;
                if(nextx >= FIELD_WIDTH) nextx = 0;
                if(nexty >= FIELD_HEIGHT) nexty = 0;
                if(matrix[nexty][nextx]) neibsCount++;
            }
            if(matrix[i][j]){
                if(neibsCount < 2 || neibsCount > 3)
                    buffer[i][j] = 0;
                else
                    buffer[i][j] = 1;
            } else {
                if(neibsCount == 3)
                    buffer[i][j] = 1;
                else
                    buffer[i][j] = 0;
            }
        }
    }
    swap(buffer, matrix);
}

void drawGrid(){
    glPointSize(1.0);
    for(int i = 0; i < WINDOW_WIDTH; i += CELL_SIZE){
        glBegin(GL_LINES);
            glColor3f(black.r, black.g, black.b);
            glVertex2i(i, 0);
            glColor3f(black.r, black.g, black.b);
            glVertex2i(i, WINDOW_HEIGHT);
        glEnd();
    }
    for(int i = 0; i < WINDOW_HEIGHT; i += CELL_SIZE){
        glBegin(GL_LINES);
            glColor3f(black.r, black.g, black.b);
            glVertex2i(0, i);
            glColor3f(black.r, black.g, black.b);
            glVertex2i(WINDOW_WIDTH, i);
        glEnd();
    }
}

void renderScene() {
	glClearColor(white.r + 0.2f, white.g, white.b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawGrid();
    for(int i = 0; i < FIELD_HEIGHT; i++){
        for(int j = 0; j < FIELD_WIDTH; j++){
            if(matrix[i][j]){
                drawQuad(i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE, CELL_SIZE, black);
            }
        }
    }
    if(time % 10 == 0)
        nextTick();
    time++;
    glutSwapBuffers();
}


void reshape(int w, int h)
{
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void mouseHandler(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        for(int i = 0; i < FIELD_HEIGHT; i++){
        for(int j = 0; j < FIELD_WIDTH; j++){
            matrix[i][j] = (rand() % 4 > 0 ? 0 : 1);
        }
    }
    }
}


int main(int argc, char *argv[])
{
    black.r = 0.0;
    black.g = 0.0;
    black.b = 0.0;
    white.r = 1.0;
    white.g = 1.0;
    white.b = 1.0;
    matrix = new int *[FIELD_HEIGHT];
    buffer = new int *[FIELD_HEIGHT];
    for(int i = 0; i < FIELD_HEIGHT; i++){
        matrix[i] = new int [FIELD_WIDTH];
        buffer[i] = new int [FIELD_WIDTH];
        for(int j = 0; j < FIELD_WIDTH; j++){
            matrix[i][j] = (rand() % 7 > 0 ? 0 : 1);
        }
    }
    cout << "Arrays created!" << endl;
    matrix[0][0] = 1;
    matrix[1][1] = 1;
    matrix[1][5] = 1;
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	//glClearColor(white.r, white.g, white.b, 1.0f);
	//glutInitWindowSize(1280,1024);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("<Жизнь>");
    glutDisplayFunc(renderScene);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseHandler);
    glutIdleFunc(renderScene);
	glutMainLoop();
    for(int i = 0; i < FIELD_HEIGHT; i++){
        delete matrix[i];
        delete buffer[i];
    }
    delete matrix;
    delete buffer;
    cout << "Arrays deleted!" << endl;
    return EXIT_SUCCESS;
}
