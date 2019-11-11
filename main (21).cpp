#include<windows.h>
#include <GL/glut.h>    // Header File For The GLUT Library
#include <GL/gl.h>    // Header File For The OpenGL32 Library
#include <GL/glu.h>    // Header File For The GLu32 Library
//#include <unistd.h>     // Header File For sleeping.

/* ASCII code for the escape key. */
#define ESCAPE 27

/* The number of our GLUT window */
int window;

// define values of rotation object
float rotate = 0.0f;
float rotation = 0.0f;

/* moving car object*/
float moveY = -0.2f;
float moveX = 0.0f;

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
// We call this right after our OpenGL window is created.
void InitGL(int Width, int Height)
{
  // This Will Clear The Background Color To Green
  glClearColor(0.0f, 0.7f, 0.3f, 0.0f); // green color background
  //glClearColor (0.5f, 0.5f, 0.5f, 0.5f);  // grey color background
  glClearDepth(1.0);                // Enables Clearing Of The Depth Buffer
  glDepthFunc(GL_LESS);                // The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);            // Enables Depth Testing

//  glEnable(GL_LIGHTING);
  //glEnable(GL_COLOR_MATERIAL);

  glShadeModel(GL_SMOOTH);            // Enables Smooth Color Shading

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();                // Reset The Projection Matrix

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);

  glMatrixMode(GL_MODELVIEW);
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
  if (Height==0)                // Prevent A Divide By Zero If The Window Is Too Small
    Height=1;

  glViewport(0, 0, Width, Height);        // Reset The Current Viewport And Perspective Transformation

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
  glMatrixMode(GL_MODELVIEW);
}

void drawTrackAspal(void) {
     glBegin(GL_QUADS);
     glColor3f(0.5f,0.5f,0.5f);  // Set The Color To Grey
     glVertex3f(-4.0f, 1.5f, 0.0f);  // Top left
     glVertex3f(4.0f, 1.5f, 0.0f);   // Top Right
     glVertex3f(4.0f, -1.5f, 0.0f);
     glVertex3f(-4.0f, -1.5f, 0.0f);
     glEnd();
}

void drawSparatorBlack(void) {
     glBegin(GL_QUADS);
     glColor3f(0.0f,0.0f,0.0f);       // Set The Color To black
     //glTranslatef(0.0f,0.0f,0.0f);
     glVertex3f(-4.0f, 1.5f, 0.0f);  // Top left
     glVertex3f(4.0f, 1.5f, 0.0f);   // Top Right
     glVertex3f(4.0f, 1.25f, 0.0f);
     glVertex3f(-4.0f, 1.25f, 0.0f);

     //glTranslatef(0.0f,-2.5f,0.0f);
     glVertex3f(-4.0f, -1.25f, 0.0f);   // Top left
     glVertex3f(4.0f, -1.25f, 0.0f);    // Top Right
     glVertex3f(4.0f, -1.5f, 0.0f);
     glVertex3f(-4.0f, -1.5f, 0.0f);
     glEnd();
}

void drawSparatorWhiteHide(void) {
     glBegin(GL_QUADS);
     glColor3f(1.0f,1.0f,1.0f);        // Set The Color To white
     glVertex3f(-5.5f, 1.49f, 0.0f);  // Top left
     glVertex3f(-4.0f, 1.49f, 0.0f);  // Top Right
     glVertex3f(-4.0f, 1.27f, 0.0f);
     glVertex3f(-5.5f, 1.27f, 0.0f);
     glEnd();
}

//float sepX= 0.0f;
//float sepY= 0.0f;
//float sepZ= 0.0f;
void drawSparatorWhiteA(void) {
     glBegin(GL_QUADS);
     glColor3f(1.0f,1.0f,1.0f);        // Set The Color To white
     //glTranslatef(sepX,sepY,sepZ);
     glVertex3f(-2.5f, 1.49f, 0.0f);   // Top left
     glVertex3f(-1.0f, 1.49f, 0.0f);   // Top Right
     glVertex3f(-1.0f, 1.27f, 0.0f);
     glVertex3f(-2.5f, 1.27f, 0.0f);
     glEnd();
}

void drawSparatorWhiteB(void) {
     glBegin(GL_QUADS);
     glColor3f(1.0f,1.0f,1.0f);        // Set The Color To white
     glVertex3f(0.5f, 1.49f, 0.0f);    // Top left
     glVertex3f(2.0f, 1.49f, 0.0f);    // Top Right
     glVertex3f(2.0f, 1.27f, 0.0f);
     glVertex3f(0.5f, 1.27f, 0.0f);
     glEnd();
}

void drawSparatorWhiteC(void) {
     glBegin(GL_QUADS);
     glColor3f(1.0f,1.0f,1.0f);        // Set The Color To White
     glVertex3f(3.5f, 1.49f, 0.0f);    // Top left
     glVertex3f(5.0f, 1.49f, 0.0f);    // Top Right
     glVertex3f(5.0f, 1.27f, 0.0f);
     glVertex3f(3.5f, 1.27f, 0.0f);
     glEnd();
}

void drawCrossLine(void) {
     glBegin(GL_QUADS);
     glColor3f(1.0f,1.0f,0.0f);        // Set The Color To YELLOW
     glVertex3f(-3.0f, -0.5f, 0.0f);   // Top left
     glVertex3f(-1.0f, -0.5f, 0.0f);   // Top Right
     glVertex3f(-1.0f, -0.7f, 0.0f);
     glVertex3f(-3.0f, -0.7f, 0.0f);
     glEnd();
}

void drawMobil(void) {
     // top front lamp
     glTranslatef(0.0f,0.0f,0.0f);
     glBegin(GL_QUADS);
     glColor3f(1.0f,1.0f,0.0f);         // Set The Color To Yellow
     glVertex3f(0.07f, -0.17f, 0.0f);   // Top left
     glVertex3f(0.21f, -0.17f, 0.0f);   // Top Right
     glVertex3f(0.21f, -0.28f, 0.0f);
     glVertex3f(0.07f, -0.28f, 0.0f);
     glEnd();

     // bottom front lamp
     glTranslatef(0.0f,0.75f,0.0f);
     glBegin(GL_QUADS);
     glColor3f(1.0f,1.0f,0.0f);         // Set The Color To Yellow
     glVertex3f(0.07f, -0.17f, 0.0f);   // Top left
     glVertex3f(0.21f, -0.17f, 0.0f);   // Top Right
     glVertex3f(0.21f, -0.28f, 0.0f);
     glVertex3f(0.07f, -0.28f, 0.0f);
     glEnd();

     // back lamp
     glTranslatef(0.0f,0.0f,0.0f);
     glBegin(GL_QUADS);
     glColor3f(1.0f,0.0f,0.0f);         // Set The Color To Red
     glVertex3f(1.94f, -0.22f, 0.0f);   // Top left
     glVertex3f(2.0f, -0.22f, 0.0f);    // Top Right
     glVertex3f(2.0f, -0.97f, 0.0f);
     glVertex3f(1.94f, -0.97f, 0.0f);
     glEnd();

     // left window
     glTranslatef(0.0f,0.0f,0.0f);
     glBegin(GL_QUADS);
     glColor3f(0.5f,0.5f,0.4f);         // Set The Color To soft Grey
     glVertex3f(0.32f, -0.31f, 0.0f);   // Top left
     glVertex3f(0.32f, -0.9f, 0.0f);    // Bottom Left
     glVertex3f(0.52f, -0.76f, 0.0f);
     glVertex3f(0.52f, -0.45f, 0.0f);
     glEnd();

     // top window
     glTranslatef(0.0f,0.0f,0.0f);
     glBegin(GL_QUADS);
     glColor3f(0.5f,0.5f,0.4f);         // Set The Color To soft Grey
     glVertex3f(0.35f, -0.28f, 0.0f);   // Top left
     glVertex3f(1.8f, -0.28f, 0.0f);    // Top Right
     glVertex3f(1.61f, -0.41f, 0.0f);
     glVertex3f(0.54f, -0.41f, 0.0f);
     glEnd();

     // right window
     glTranslatef(0.0f,0.0f,0.0f);
     glBegin(GL_QUADS);
     glColor3f(0.5f,0.5f,0.4f);  // Set The Color To soft Grey
     glVertex3f(1.83f, -0.31f, 0.0f);     // Top Right
     glVertex3f(1.83f, -0.9f, 0.0f);      // Bottom Right
     glVertex3f(1.63f, -0.76f, 0.0f);
     glVertex3f(1.63f, -0.45f, 0.0f);
     glEnd();

     // bottom window
     glTranslatef(0.0f,0.0f,0.0f);
     glBegin(GL_QUADS);
     glColor3f(0.5f,0.5f,0.4f);  // Set The Color To soft Grey
     glVertex3f(0.35f, -0.93f, 0.0f);   // Bottom Left
     glVertex3f(1.8f, -0.93f, 0.0f);   // Bottom Right
     glVertex3f(1.61f, -0.79f, 0.0f);
     glVertex3f(0.54f, -0.79f, 0.0f);
     glEnd();

     // body
     glTranslatef(0.0f,0.0f,0.0f);
     glBegin(GL_QUADS);
     glColor3f(0.0f,0.0f,0.0f);         // Set The Color To Black
     glVertex3f(0.0f, -0.1f, 0.0f);     // Top left
     glVertex3f(2.0f, -0.1f, 0.0f);
     glVertex3f(2.0f, -1.1f, 0.0f);
     glVertex3f(0.0f, -1.1f, 0.0f);
     glEnd();
}

/* The main drawing function. */
void DrawGLScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        // Clear The Screen And The Depth Buffer
  glLoadIdentity();                // Reset The View

/* Mobil*/
  glPushMatrix();
      glTranslatef(moveX,moveY,-6.0f);
      drawMobil();
  glPopMatrix();

/* yellow line*/
  glPushMatrix();
      glTranslatef(rotate,0.6f,-6.0f);
      drawCrossLine();
      rotate += 0.015f;
      if(rotate>7.0f)
         rotate = -4.5f;
  glPopMatrix();


/* white separator*/
// top separator
  glPushMatrix();
      glTranslatef(rotation,0.0f,-6.0f);
      drawSparatorWhiteHide();
      drawSparatorWhiteA();
      drawSparatorWhiteB();
      drawSparatorWhiteC();
  glPopMatrix();

// bottom separator
  glPushMatrix();
      glTranslatef(rotation,-2.76f,-6.0f);
      drawSparatorWhiteHide();
      drawSparatorWhiteA();
      drawSparatorWhiteB();
      drawSparatorWhiteC();
  glPopMatrix();

  rotation += 0.015f;
  if(rotation>3.0f)
      rotation = 0.0f;

  glPushMatrix();
      glTranslatef(0.0f,0.0f,-6.0f);
      drawSparatorBlack();
  glPopMatrix();

  glPushMatrix();
      glTranslatef(0.0f,0.0f,-6.0f);
      drawTrackAspal();
  glPopMatrix();

  // swap the buffers to display, since double buffering is used.
  glutSwapBuffers();
}


/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y)
{
    /* sleep to avoid thrashing this procedure */
   // usleep(100);

    /* If escape is pressed, kill everything. */
    if (key == ESCAPE)
    {
    /* shut down our window */
    glutDestroyWindow(window);

    /* exit the program...normal termination. */
    exit(0);
    }

float inc = 0.1f;
    switch (key) {
        case 'w': //up
         if(moveY>0.55f) inc=0;  //limit move up to separator
         moveY = moveY+inc;
         glutPostRedisplay();
        break;
        case 's': //down
         if(moveY< -0.9f) inc=0;  //limit move down to separator
         moveY = moveY-inc;
         glutPostRedisplay();
        break;
        case 'a': //forward
         if(moveX< -4.0f) inc=0;  //limit move forward
         moveX = moveX-inc;
         glutPostRedisplay();
        break;
        case 'd': //reverse       //limit move reverse
         if(moveX>2.0f) inc=0;
         moveX = moveX+inc;
         glutPostRedisplay();
        break;
     }
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);

  /* get a 640 x 480 window */
  glutInitWindowSize(640, 400);

  /* the window starts at the upper left corner of the screen */
  glutInitWindowPosition(0, 0);

  /* Open a window */
  window = glutCreateWindow("Balap Mobil");

  /* Register the function to do all our OpenGL drawing. */
  glutDisplayFunc(&DrawGLScene);


  //PlaySound("starwars.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);

  /* Go fullscreen.  This is as soon as possible. */
  //glutFullScreen();

  /* Even if there are no events, redraw our gl scene. */
  glutIdleFunc(&DrawGLScene);

  /* Register the function called when our window is resized. */
  glutReshapeFunc(&ReSizeGLScene);

  /* Register the function called when the keyboard is pressed. */
  glutKeyboardFunc(&keyPressed);

  /* Initialize our window. */
  InitGL(640, 480);

  /* Start Event Processing Engine */
  glutMainLoop();

  return 1;
}
