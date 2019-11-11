#include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#define PI acos(-1.0)


static GLfloat m1 = -60, m2=-52;
static GLfloat n1 = -60, n2=-52, c=-57;
static GLfloat p1 = -60, p2=-52, b=-54;
static GLfloat q1 =  32, q2=40;


static GLfloat s1 =-8,s2 =-8;
static GLfloat w = 0;
static GLfloat h1 = 0;
static GLfloat J = -2;


static GLfloat cl1 =  32, cl2=40;

static GLfloat tx1=100,tx2=100,tx3 =100,tx4 =100,tx5 =100,tx6 =100; // for conversation msg

static GLfloat tx7 =100,tx8 =100,tx9 =100,tx6s=100;

static GLfloat tx10=100,tx11 =100,tx12 =100,tx13 =100,tx6t=100;

static GLfloat v_cloud_r=-50,v_cloud_l=50;


int sc=0,mx1=-40,gx1=-32,mx2=-40,gx2=-32,mx3=-40,gx3=-32;


void spinDisplay(void)

{

        w+=0.3;

        s1+=0.09;
        if(s1>=12)
        s1=-8;


        s2+=0.09;  // Wing 2
        if(s2>=12)
        s2=-8;

	    v_cloud_l -=0.02; // Cloud 1
       if(v_cloud_l > -50)
		//v_cloud_r = -1;

		v_cloud_r += 0.02;  // Cloud 2
       if(v_cloud_r > 50)
		//v_cloud_l = 8;


		w+=0.3;
//



       glutPostRedisplay();

}

void anim1stwin()
{
    /************************************************* first windows text show*****************************************/
		m1 += 0.06;   // man walk
		m2 += 0.06;   //girl  walk
       if(m1 > 40)
            //m1=40;
                     //    here i take girl position for text view
        if(m2 > 95)
        {
		//m2 = 48;
		tx6=-10;              //tx6 press Enter
        }
        if(m2>-45)
        {
            tx1=-10;
        }

        if(m2>-34)
        {
            tx1=100;
        }
        if(m2>-32)
        {
            tx2=-10;
        }


        if(m2>-24)
        {
            tx2=100;
        }


        if(m2>16)
        {
            tx3=-10;
        }

        if(m2>26)
        {
            tx3=100;
        }


        if(m2>26)
        {
            tx4=-10;
        }

        if(m2>38)
        {
            tx4=100;
        }


        if(m2>40)
        {
            tx5=-10;
        }

        if(m2>50)
        {
            tx5=100;
        }

        glutPostRedisplay();
}

void anim2ndwin()
{

/************************************************* Second windows text show *****************************************/



        n1 += 0.06;   // man walk
		n2 += 0.06;   //girl  walk
		c+=0.06;// car

       if(n1 > 40)
         //   n1=40;
                     //    here i take girl position for text view
        if(n2 > 95)
        {
		//n2 = 48;
		tx6s=-10;              //tx6 press Enter
        }



       if(n2>-30)
       {
           tx7=-10;
       }
       if(n2>-18)
       {
           tx7=100;
       }


       if(n2>-16)
       {
           tx8=-16;
       }
       if(n2>-4)
       {
           tx8=100;
       }


        if(n2>10)
       {
           tx9=-10;
       }
       if(n2>22)
       {
           tx9=100;
       }

	glutPostRedisplay();
}

void anim3rdwin()
{

/************************************************* Third windows text show *****************************************/



        p1 += 0.06;   // man walk
		p2 += 0.06;   //girl  walk
		b+=0.06;
       if(p1 > 32)
            p1=32;
                     //    here i take girl position for text view
        if(p2 > 40)
        {
        b=38;
		p2 = 40;
		tx6t=-10;              //tx6 press Enter
        }



       if(p2>-40)
       {
           tx10=-16;
       }
       if(p2>-32)
       {
           tx10=100;
       }



       if(p2>0)
       {
           tx11=-16;
       }
       if(p2>6)
       {
           tx11=100;
       }


        if(p2>7)
       {
           tx12=-16;
       }
       if(p2>13)
       {
           tx12=100;
       }

	glutPostRedisplay();
}


void circle(GLdouble rad)
{
	GLint points = 50;
	GLdouble delTheta = (2.0 * PI) / (GLdouble)points;
	GLdouble theta = 0.0;

	glBegin(GL_POLYGON);
	{
		for( GLint i = 0; i <=50; i++, theta += delTheta )
		{
			glVertex2f(rad * cos(theta),rad * sin(theta));
		}
	}
	glEnd();
}

void half_circle(GLdouble rad)
{
	GLint points = 50;
	GLdouble delTheta = (2.0 * PI) / (GLdouble)points;
	GLdouble theta = 0.0;

	glBegin(GL_POLYGON);
	{
		for( GLint i = 0; i <=25; i++, theta += delTheta )
		{
			glVertex2f(rad * cos(theta),rad * sin(theta));
		}
	}
	glEnd();
}

void pond()
{
glColor3f(0.7,0.7,0.85);
glBegin(GL_POLYGON);
glVertex2f(0.25,3.50);
glVertex2f(0.25,3.75);
glVertex2f(0.50,4.00);
glVertex2f(0.75,4.10);
glVertex2f(1.00,4.20);
glVertex2f(2.00,4.20);
glVertex2f(2.25,4.10);
glVertex2f(2.50,4.05);
glVertex2f(2.75,3.90);
glVertex2f(3.00,3.75);
glVertex2f(3.10,3.50);
glVertex2f(3.00,3.20);
glVertex2f(2.75,3.00);
glVertex2f(2.50,2.95);
glVertex2f(2.25,2.90);
glVertex2f(2.00,2.85);
glVertex2f(1.75,2.80);
glVertex2f(1.50,2.80);
glVertex2f(1.25,2.80);
glVertex2f(1.00,2.90);
glVertex2f(0.75,3);
glVertex2f(0.50,3.10);
glEnd();
}

void drawDisk(double radius) {
	int d;
	glBegin(GL_POLYGON);
	for (d = 0; d < 32; d++) {
		double angle = 2*PI/32 * d;
		glVertex2d( radius*cos(angle), radius*sin(angle));
	}
	glEnd();
}

void drawWheel() {
    int i;
	glColor3f(0,0,0);
	drawDisk(1);
	glColor3f(0.75f, 0.75f, 0.75f);
	drawDisk(.9);
	glColor3f(0,0,0);
	drawDisk(0.1);
	glRotatef(w,0,0,-1);
	glBegin(GL_LINES);
	for (i = 0; i < 15; i++) {
		glVertex2f(0,0);
		glVertex2d(cos(i*2*PI/15), sin(i*2*PI/15));
	}
	glEnd();
}

void cloud()

{
	//left

	glPushMatrix();
	glTranslatef(4,5.5,0);
	circle(4);
	glPopMatrix();

	//right

	glPushMatrix();
	glTranslatef(-8,5.5,0);
	circle(3.5);
	glPopMatrix();

	//top left

	glPushMatrix();
	glTranslatef(-3.5,9,0);
	circle(3.5);
	glPopMatrix();

	//top right

	glPushMatrix();
	glTranslatef(1,9,0);
	circle(3);
	glPopMatrix();

	//middle

	glPushMatrix();

	glColor3f (1, 1 ,1);
	glTranslatef(-1.5,5.5,0);
	circle(4);
	glPopMatrix();

}
void bird()
{
      glPushMatrix();
      glRotatef(s2,0,0,1);
      glBegin(GL_TRIANGLES);
      glColor3f(0.0f, 0.0f, 0.0f);
      glVertex2f(.1,.7);
      glVertex2f(.4,.3);
      glVertex2f(.4,.1);
      glEnd();
      glPopMatrix();

      glPushMatrix();
      glRotatef(s1,1,1,-1);
      glBegin(GL_TRIANGLES);
      glColor3f(0.0f, 0.0f, 0.0f);
      glVertex2f(.7,.7);
      glVertex2f(.4,.3);
      glVertex2f(.4,.1);
   glEnd();
   glPopMatrix();

   glBegin(GL_POLYGON);
      glColor3f(0.0f, 0.0f, 0.0f);
      glVertex2f(.4,.1);
      glVertex2f(.5,.2);
      glVertex2f(.4,.4);
      glVertex2f(.3,.2);
      glEnd();
}

void river()
{
    glColor3f(0.47f,0.73f,1.0f);//rever
glBegin(GL_POLYGON);
  glVertex2f(-50,20);
  glVertex2f(-10,20);
   glVertex2f(-15,15);
    glVertex2f(-22,6);
     glVertex2f(-28,-3);
      glVertex2f(-30,-9);

   glVertex2f(-37,-25);
   glVertex2f(-50,-30);
  glEnd();
  glColor3f(0.41f,0.70f,1.0f);
glBegin(GL_POLYGON);
  glVertex2f(-50,20);
  glVertex2f(-20,20);
   glVertex2f(-25,20);
    glVertex2f(-30,10);
     glVertex2f(-40,0);
      glVertex2f(-50,-15);


  glEnd();
}

void tree()
{
    glColor3f(0.0f,0.43f,0.0f);//tree 1
glBegin(GL_QUADS);
  glVertex2f(44,-22);
  glVertex2f(46,-22);
   glVertex2f(46,-26);
    glVertex2f(44,-26);
     glEnd();
     glColor3f(0.0f,0.43f,0.0f);
     glBegin(GL_TRIANGLES);
  glVertex2f(40,-22);
  glVertex2f(45,-17);
   glVertex2f(50,-22);

     glEnd();
     glColor3f(0.0f,0.43f,0.0f);
     glBegin(GL_TRIANGLES);
  glVertex2f(41,-18);
  glVertex2f(45,-14);
   glVertex2f(49,-18);

     glEnd();
     glColor3f(0.0f,0.43f,0.0f);
     glBegin(GL_TRIANGLES);
  glVertex2f(42,-15);
  glVertex2f(45,-10);
   glVertex2f(48,-15);

     glEnd();
}
void house()
{
    glColor3f(0.0,0.0,1.0);

    glBegin(GL_POLYGON);
    glVertex3f(0,0,0);
    glVertex3f(-25,0,0);
    glVertex3f(-25,15,0);
    glVertex3f(0,15,0);

    glEnd();

    glColor3f(0.0,1.0,1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-30,15,0);
    glVertex3f(-12,30,0);
    glVertex3f(5,15,0);


    glEnd();
     glColor3f(1.0,0.0,0.0);
     glPushMatrix();
    //glScalef(-5,-5,0);
glTranslatef(-5,10,0);

    glBegin(GL_POLYGON);
    glVertex3f(0,0,0);
    glVertex3f(-5,0,0);
    glVertex3f(-5,5,0);
    glVertex3f(0,5,0);

    glEnd();
    glPopMatrix();

    glColor3f(0.25,0.25,0.25);
     glPushMatrix();
    //glScalef(-5,-5,0);
glTranslatef(-15,0,0);

    glBegin(GL_POLYGON);
    glVertex3f(0,0,0);
    glVertex3f(-5,0,0);
    glVertex3f(-5,7,0);
    glVertex3f(0,7,0);

    glEnd();
    glPopMatrix();

}
void road()
{
    glColor3f(0.35f,0.35f,0.35f);//rood

glBegin(GL_QUADS);
  glVertex2f(-50,-25);
  glVertex2f(50,-25);
   glVertex2f(50,-40);
    glVertex2f(-50,-40);
     glEnd();
     glColor3f(1.000, 0.843, 0.000);
     glLineWidth(6);
glBegin(GL_LINES);

  glVertex2f(-50,-30);
  glVertex2f(50,-30);

    glEnd();
}

void sun()
{
    //line
glPushMatrix();
glTranslatef(5.2, 3.8, 0);
glColor3f(1.0f,1.0f,0.2f);
glLineWidth(2);
glBegin(GL_LINES);

  glVertex2f(40,30);
  glVertex2f(40,23);

    glEnd();
glColor3f(1.0f,1.0f,0.2f);
     glLineWidth(2);
glBegin(GL_LINES);

  glVertex2f(40,30);
  glVertex2f(35,25);

    glEnd();
    glColor3f(1.0f,1.0f,0.2f);
     glLineWidth(2);
glBegin(GL_LINES);

  glVertex2f(40,30);
  glVertex2f(34,30);

    glEnd();
    glColor3f(1.0f,1.0f,0.2f);
     glLineWidth(2);
glBegin(GL_LINES);

  glVertex2f(40,30);
  glVertex2f(35,34);

    glEnd();
glColor3f(1.0f,1.0f,0.2f);
     glLineWidth(2);
glBegin(GL_LINES);

  glVertex2f(40,30);
  glVertex2f(40,37);

    glEnd();
    glColor3f(1.0f,1.0f,0.2f);
     glLineWidth(2);
glBegin(GL_LINES);

  glVertex2f(40,30);
  glVertex2f(45,34);

    glEnd();
    glColor3f(1.0f,1.0f,0.2f);
     glLineWidth(2);
glBegin(GL_LINES);

  glVertex2f(40,30);
  glVertex2f(46,30);

    glEnd();
    glColor3f(1.0f,1.0f,0.2f);
     glLineWidth(2);
glBegin(GL_LINES);

  glVertex2f(40,30);
  glVertex2f(45,25);
    glEnd();
    glPopMatrix();

    glPushMatrix();//sun
glColor3f(1, 0.6, 0.1);
glTranslatef(40, 30, 10);
glutSolidSphere(4, 100, 100);
glPopMatrix();

glPushMatrix();
glColor3f(1,0.7,0);
glTranslatef(40, 30, 10);
glutSolidSphere(3.5, 50, 50);
glPopMatrix();

glPushMatrix();
glColor3f(1,0.8,0.4);
glTranslatef(40, 30, 10);
glutSolidSphere(3, 50, 50);
glPopMatrix();

glPushMatrix();
glColor3f(1,0.9,0.3);
glTranslatef(40, 30, 10);
glutSolidSphere(2.5, 50, 50);
glPopMatrix();

glPushMatrix();
glColor3f(1,1,0.2);
glTranslatef(40, 30, 10);
glutSolidSphere(2, 50, 50);
glPopMatrix();

}

void hills()
{
    glColor3f(0.0f,0.43f,0.0f);
glBegin(GL_POLYGON);
  glVertex2f(-25,20);
  glVertex2f(-15,32);
   glVertex2f(-7,20);
    glVertex2f(5,35);
     glVertex2f(15,25);
      glVertex2f(20,27);

   glVertex2f(30,20);

  glEnd();
  glColor3f(0.0f,0.43f,0.0f);
glBegin(GL_POLYGON);
  glVertex2f(-50,20);
  glVertex2f(-40,30);
   glVertex2f(-35,25);
    glVertex2f(-25,35);
     glVertex2f(-20,20);


  glEnd();

       glColor3f(0.0f,0.43f,0.0f);
glBegin(GL_POLYGON);
  glVertex2f(65,20);
  glVertex2f(75,32);
   glVertex2f(73,20);
    glVertex2f(85,35);
     glVertex2f(95,25);
      glVertex2f(100,27);
glVertex2f(110,20);
   //
    glColor3f(0.0f,0.43f,0.0f);
glBegin(GL_POLYGON);
  glVertex2f(10,20);
  glVertex2f(20,30);
   glVertex2f(25,25);
    glVertex2f(45,35);
     glVertex2f(40,20);

    glEnd();

}


void sky()
{

	glPushMatrix();
	glColor3f(0.196078, 0.6, 0.8);
	glBegin(GL_POLYGON);

	glVertex3f (-76,42, 0.0);
    glVertex3f (-76,8, 0.0);
    glVertex3f (76,8, 0.0);
    glVertex3f (76,42, 0.0);

    glEnd();
	glPopMatrix();
}


void ground()
{
//green

	glColor3f(0.196, 0.804, 0.196);
	glPushMatrix();
	glTranslatef(0,-1,0);
	glBegin(GL_POLYGON);

	glVertex3f (-100, -50, 0.0);
    glVertex3f (-100,10, 0.0);
    glVertex3f (100,10, 0.0);
    glVertex3f (100,-50, 0.0);

    glEnd();
	glPopMatrix();

}
//man

void man()
{
//head
    glPushMatrix();
    glColor3f(1.000, 0.894, 0.710);
    glTranslatef(-18,0,0);
    glScalef(1.8,2.2,0);
    circle(2);
	glPopMatrix();
//eye
    glPushMatrix();
    glColor3f(1.000, 1.000, 1.000);
    glTranslatef(-18.5,0,0);
    glScalef(2,2,3);
    glBegin(GL_TRIANGLES);
    glVertex3f(2,0,0);
    glVertex3f(1,.5,0);
    glVertex3f(2,.9,1);
    glEnd();
	glPopMatrix();
//eye_point
	glPushMatrix();
    glColor3f(0.000, 0.000, 0.000);
    glTranslatef(-15,1,0);
    //glScalef(1,1,0);
    circle(.5);
    glEnd();
	glPopMatrix();


//mouth
    glPushMatrix();
    glColor3f(0.000, 0.000, 0.000);
    glTranslatef(-18.6,-4,0);
    glScalef(2,2,3);
    glBegin(GL_TRIANGLES);
    glVertex3f(2,.8,0);
    glVertex3f(0.6,1,0);
    glVertex3f(2,1.2,1);
    glEnd();
	glPopMatrix();

//hair
    glPushMatrix();
    glColor3f(0.0,0.0,0.0);
    glTranslatef(-18,-4,0);
    glScalef(2.5,2.4,3);
    glBegin(GL_POLYGON);
    glVertex3f(1,2.6,0.0);
    glVertex3f(1.9,2.8,0);
    glVertex3f(1,3.6,0.0);
    glVertex3f(0.2,3.9,0.0);
    glVertex3f(-.9,3.9,0.0);
    glVertex3f(-1.4,3.5,0.0);
    glVertex3f(-1.8,3.1,0.0);
    glVertex3f(-2.0,2.7,0.0);
    glVertex3f(-2.1,2.4,0.0);
    glVertex3f(-2.2,2.1,0.0);
    glVertex3f(-2.3,1.8,0.0);
    glVertex3f(-2.2,1.5,0.0);
    glVertex3f(-2.1,1.2,0.0);
    glVertex3f(-1.3,1.2,0.0);
    glVertex3f(-1.1,1.4,0.0);
    glVertex3f(-0.9,1.6,0.0);
    glVertex3f(-0.7,1.8,0.0);
    glVertex3f(-0.4,2.0,0.0);
    glVertex3f(-0.1,2.2,0.0);
    glVertex3f(0.1,2.4,0.0);
    glVertex3f(0.6,2.6,0.0);
    glEnd();
    glPopMatrix();
//neck
    glPushMatrix();
    glColor3f(1.000, 0.894, 0.710);
    glTranslatef(-18,0,0);
    glScalef(2,2.6,0);
    glBegin(GL_POLYGON);
    glVertex3f(-.7,-1.0,0.0);
    glVertex3f(-.7,-4,0.0);
    glVertex3f(.4,-2.8,0.0);
    glVertex3f(.4,-1,0);
    glEnd();
	glPopMatrix();



// BODY
    glPushMatrix();
    glColor3f(0.118, 0.565, 1.000);
    glTranslatef(-18.1,2.6,0);
    glScalef(1.4,3.2,3);
    glBegin(GL_POLYGON);
    glVertex3f(-1.9,-2.6,0);
    glVertex3f(-2.0,-2.7,0);
    glVertex3f(-1.9,-2.9,0);
    glVertex3f(-1.8,-3.1,0);
    glVertex3f(-2.0,-5.5,0);
    glVertex3f(-1.9,-5.6,0);
    glVertex3f(1.6,-5.6,0);
    glVertex3f(1.7,-5.5,0);

    glVertex3f(1.7,-2.6,0);
    glVertex3f(1.6,-2.5,0);
    glEnd();
	glPopMatrix();



//hand_y
    glPushMatrix();
    glColor3f(1.000, 0.894, 0.710);
    glTranslatef(-20,-12,0);
    glScalef(1.2,1,0);
    glBegin(GL_POLYGON);
	glVertex3f(1,3,0);
    glVertex3f(2.3,3,0);
    glVertex3f(2.3,-1,0);
    glVertex3f(1,-1,0);
    glEnd();
	glPopMatrix();

//hand_x
    glPushMatrix();
    glColor3f(1.000, 0.894, 0.710);
    glTranslatef(-18,-13,0);
    glScalef(1.2,1.4,0);
    glBegin(GL_POLYGON);
	glVertex3f(0,1,0);
    glVertex3f(4,1,0);
    glVertex3f(4,0,0);
    glVertex3f(0,0,0);
    glEnd();
	glPopMatrix();


//hand_up
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-20.8,-10,0);
    glScalef(2,0,0);
    glBegin(GL_LINES);
    glVertex3f(2,1,0);
    glVertex3f(2,0,0);
    glEnd();
	glPopMatrix();

//leg 1
	glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-18,0,0);
    glScalef(1.4,2.6,3);
    glBegin(GL_POLYGON);
    glVertex3f(-1.9,-5.6,0);
    glVertex3f(-1.9,-8.6,0);
    glVertex3f(-1.0,-8.6,0);
    glVertex3f(-0.0,-5.6,0);

    glEnd();
	glPopMatrix();
//leg 2
	glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(-18,0,0);
    glScalef(1.4,2.6,3);
    glBegin(GL_POLYGON);
    glVertex3f(-0.2,-5.6,0);
    glVertex3f(-0.0,-8.6,0);
    glVertex3f(0.9,-8.6,0);
    glVertex3f(1.5,-5.6,0);

    glEnd();
	glPopMatrix();

//feet 1
    glPushMatrix();
    glColor3f(0, 0.000, 0);
    glTranslatef(-18,0,0);
    glScalef(1.6,2.6,3);
    glBegin(GL_POLYGON);
    glVertex3f(-0.9,-8.0,0);
    glVertex3f(-1.0,-8.6,0);
    glVertex3f(-.1,-8.6,0);
    glVertex3f(-0.9,-8,0);


    glEnd();
	glPopMatrix();

//feet 2
    glPushMatrix();
    glColor3f(0.0, 0.000, 0);
    glTranslatef(-18.2,0,0);
    glScalef(1.6,2.6,3);
    glBegin(GL_POLYGON);
    glVertex3f(1.0,-8.0,0);
    glVertex3f(0.9,-8.6,0);
    glVertex3f(1.8,-8.6,0);
    glVertex3f(1.0,-8.0,0);


    glEnd();
	glPopMatrix();

}

//girl


void girl()
{
//head
    glPushMatrix();
    glColor3f(1.000, 0.894, 0.710);
    glTranslatef(-18,0,0);
    glScalef(1.8,2.2,0);
    circle(2);
	glPopMatrix();
//eye
    glPushMatrix();
    glColor3f(1.000, 1.000, 1.000);
    glTranslatef(-18.5,0,0);
    glScalef(2,2,3);
    glBegin(GL_TRIANGLES);
    glVertex3f(2,0,0);
    glVertex3f(1,.5,0);
    glVertex3f(2,.9,1);
    glEnd();
	glPopMatrix();
//eye_point
	glPushMatrix();
    glColor3f(0.000, 0.000, 0.000);
    glTranslatef(-15,1,0);
    //glScalef(1,1,0);
    circle(.5);
    glEnd();
	glPopMatrix();


//mouth
    glPushMatrix();
    glColor3f(1.000, 0.753, 0.796);
    glTranslatef(-18.6,-4,0);
    glScalef(2,2,3);
    glBegin(GL_TRIANGLES);
    glVertex3f(2,.8,0);
    glVertex3f(0.6,1,0);
    glVertex3f(2,1.2,1);
    glEnd();
	glPopMatrix();

//hair
   //hair
   glPushMatrix();
   glColor3f(0.0,0.0,0.0);
   glTranslatef(-18,-4,0);
   glScalef(2,2.6,3);
   glBegin(GL_POLYGON);
   glVertex3f(1,2.6,0.0);
   glVertex3f(1.9,2.8,0);
   glVertex3f(1,3.6,0.0);
   glVertex3f(0.2,3.9,0.0);
   glVertex3f(-.9,3.9,0.0);
   glVertex3f(-1.4,3.5,0.0);
   glVertex3f(-1.8,3.1,0.0);
   glVertex3f(-2.2,2.1,0.0);
   glVertex3f(-2.3,1.8,0.0);
   glVertex3f(-2.2,1.5,0.0);
   glVertex3f(-2.1,1.2,0.0);
   glVertex3f(-2.0,1.0,0.0);
   glVertex3f(-1.9,0.8,0.0);
   glVertex3f(-1.8,0.6,0.0);
   glVertex3f(-1.7,0.4,0.0);
   glVertex3f(-1.6,0.2,0.0);
   glVertex3f(-1.3,1.2,0.0);
   glVertex3f(-1.1,1.4,0.0);
   glVertex3f(-0.9,1.6,0.0);
   glVertex3f(-0.7,1.8,0.0);
   glVertex3f(-0.4,2.0,0.0);
   glVertex3f(-0.1,2.2,0.0);
   glVertex3f(0.1,2.4,0.0);
   glVertex3f(0.6,2.6,0.0);
   glEnd();
   glPopMatrix();
//pony
   glPushMatrix();
   glColor3f(0.0,0.0,0.0);
   glTranslatef(-18,-4,0);
   glScalef(2,2.6,3);
   glBegin(GL_POLYGON);
   glVertex3f(-2.0,2.7,0.0);
   glVertex3f(-2.1,2.4,0.0);
   glVertex3f(-3.0,2.4,0.0);
   glVertex3f(-3.1,2.2,0.0);
   glVertex3f(-3.1,0.4,0.0);
   glVertex3f(-3.0,0.6,0.0);
   glVertex3f(-2.8,1.0,0.0);
   glVertex3f(-2.7,2.2,0.0);
   glEnd();
   glPopMatrix();
//neck
    glPushMatrix();
    glColor3f(1.000, 0.894, 0.710);
    glTranslatef(-18,0,0);
    glScalef(2,2.6,0);
    glBegin(GL_POLYGON);
    glVertex3f(-.7,-1.0,0.0);
    glVertex3f(-.7,-4,0.0);
    glVertex3f(.4,-2.8,0.0);
    glVertex3f(.4,-1,0);
    glEnd();
	glPopMatrix();



// BODY
    glPushMatrix();
    glColor3f(1.000, 0.843, 0.000);
    glTranslatef(-23,-13,0);
    glScalef(2.4,2,0);
    glBegin(GL_POLYGON);

    glVertex3f(1,3.5,0);
    glVertex3f(3,3.5,0);
    glVertex3f(3,-2,0);
    glVertex3f(1,-2,0);
    glEnd();
	glPopMatrix();
//frok

     glPushMatrix();
    glColor3f(1.000, 0.843, 0.000);
    glTranslatef(-23,-13,0);
    glScalef(2.4,2,0);
    glBegin(GL_POLYGON);

    glVertex3f(1,1,0);
    glVertex3f(3,1,0);
    glVertex3f(4,-1.5,0);
    glVertex3f(-.3,-1.5,0);
    glEnd();
	glPopMatrix();


//hand_y
    glPushMatrix();
    glColor3f(1.000, 0.894, 0.710);
    glTranslatef(-20,-12,0);
    glScalef(1.2,1,0);
    glBegin(GL_POLYGON);
	glVertex3f(1,3,0);
    glVertex3f(2.3,3,0);
    glVertex3f(2.3,-1,0);
    glVertex3f(1,-1,0);
    glEnd();
	glPopMatrix();

//hand_x
    glPushMatrix();
    glColor3f(1.000, 0.894, 0.710);
    glTranslatef(-18,-13,0);
    glScalef(1.2,1.4,0);
    glBegin(GL_POLYGON);
	glVertex3f(0,1,0);
    glVertex3f(4,1,0);
    glVertex3f(4,0,0);
    glVertex3f(0,0,0);
    glEnd();
	glPopMatrix();


//hand_up
    glPushMatrix();
    glColor3f(0.502, 0.000, 0.000);
    glTranslatef(-20.8,-10,0);
    glScalef(2,2,0);
    glBegin(GL_POLYGON);
	glVertex3f(.5,1,0);
    glVertex3f(2,1,0);
    glVertex3f(2,0,0);
    glVertex3f(.5,0,0);
    glEnd();
	glPopMatrix();

//leg 1
	glPushMatrix();
    glColor3f(1.000, 0.271, 0.000);
    glTranslatef(-18,-1,0);
    glScalef(1.6,2.6,3);
    glBegin(GL_POLYGON);
    glVertex3f(-1.9,-5.6,0);
    glVertex3f(-1.9,-8.6,0);
    glVertex3f(-1.0,-8.6,0);
    glVertex3f(-0.0,-5.6,0);

    glEnd();
	glPopMatrix();
//leg 2
	glPushMatrix();
    glColor3f(1.000, 0.271, 0.000);
    glTranslatef(-18,-1,0);
    glScalef(1.6,2.6,3);
    glBegin(GL_POLYGON);
    glVertex3f(-0.2,-5.6,0);
    glVertex3f(-0.0,-8.6,0);
    glVertex3f(0.9,-8.6,0);
    glVertex3f(1.5,-5.6,0);

    glEnd();
	glPopMatrix();

//feet 1
    glPushMatrix();
    glColor3f(1.000, 0.271, 0.000);
    glTranslatef(-18,-1,0);
    glScalef(1.6,2.6,3);
    glBegin(GL_POLYGON);
    glVertex3f(-0.9,-8.0,0);
    glVertex3f(-1.0,-8.6,0);
    glVertex3f(-.1,-8.6,0);
    glVertex3f(-0.9,-8,0);


    glEnd();
	glPopMatrix();

//feet 2
    glPushMatrix();
    glColor3f(1.000, 0.271, 0.000);
    glTranslatef(-18,-1,0);
    glScalef(1.6,2.6,3);
    glBegin(GL_POLYGON);
    glVertex3f(1.0,-8.0,0);
    glVertex3f(0.9,-8.6,0);
    glVertex3f(1.8,-8.6,0);
    glVertex3f(1.0,-8.0,0);


    glEnd();
	glPopMatrix();

}

void girl1()
{
    //head
    glPushMatrix();
    glColor3f(1.000, 0.894, 0.710);
    glTranslatef(-18,0,0);
    glScalef(1.8,2.2,0);
    circle(2);
	glPopMatrix();
//eye
    glPushMatrix();
    glColor3f(1.000, 1.000, 1.000);
    glTranslatef(-18.5,0,0);
    glScalef(2,2,3);
    glBegin(GL_TRIANGLES);
    glVertex3f(2,0,0);
    glVertex3f(1,.5,0);
    glVertex3f(2,.9,1);
    glEnd();
	glPopMatrix();
//eye_point
	glPushMatrix();
    glColor3f(0.000, 0.000, 0.000);
    glTranslatef(-15,1,0);
    //glScalef(1,1,0);
    circle(.5);
    glEnd();
	glPopMatrix();


//mouth
    glPushMatrix();
    glColor3f(1.000, 0.753, 0.796);
    glTranslatef(-18.6,-4,0);
    glScalef(2,2,3);
    glBegin(GL_TRIANGLES);
    glVertex3f(2,.8,0);
    glVertex3f(0.6,1,0);
    glVertex3f(2,1.2,1);
    glEnd();
	glPopMatrix();

//hair
   //hair
   glPushMatrix();
   glColor3f(0.0,0.0,0.0);
   glTranslatef(-18,-4,0);
   glScalef(2,2.6,3);
   glBegin(GL_POLYGON);
   glVertex3f(1,2.6,0.0);
   glVertex3f(1.9,2.8,0);
   glVertex3f(1,3.6,0.0);
   glVertex3f(0.2,3.9,0.0);
   glVertex3f(-.9,3.9,0.0);
   glVertex3f(-1.4,3.5,0.0);
   glVertex3f(-1.8,3.1,0.0);
   glVertex3f(-2.2,2.1,0.0);
   glVertex3f(-2.3,1.8,0.0);
   glVertex3f(-2.2,1.5,0.0);
   glVertex3f(-2.1,1.2,0.0);
   glVertex3f(-2.0,1.0,0.0);
   glVertex3f(-1.9,0.8,0.0);
   glVertex3f(-1.8,0.6,0.0);
   glVertex3f(-1.7,0.4,0.0);
   glVertex3f(-1.6,0.2,0.0);
   glVertex3f(-1.3,1.2,0.0);
   glVertex3f(-1.1,1.4,0.0);
   glVertex3f(-0.9,1.6,0.0);
   glVertex3f(-0.7,1.8,0.0);
   glVertex3f(-0.4,2.0,0.0);
   glVertex3f(-0.1,2.2,0.0);
   glVertex3f(0.1,2.4,0.0);
   glVertex3f(0.6,2.6,0.0);
   glEnd();
   glPopMatrix();
//pony
   glPushMatrix();
   glColor3f(0.0,0.0,0.0);
   glTranslatef(-18,-4,0);
   glScalef(2,2.6,3);
   glBegin(GL_POLYGON);
   glVertex3f(-2.0,2.7,0.0);
   glVertex3f(-2.1,2.4,0.0);
   glVertex3f(-3.0,2.4,0.0);
   glVertex3f(-3.1,2.2,0.0);
   glVertex3f(-3.1,0.4,0.0);
   glVertex3f(-3.0,0.6,0.0);
   glVertex3f(-2.8,1.0,0.0);
   glVertex3f(-2.7,2.2,0.0);
   glEnd();
   glPopMatrix();
//neck
    glPushMatrix();
    glColor3f(1.000, 0.894, 0.710);
    glTranslatef(-18,0,0);
    glScalef(2,2.6,0);
    glBegin(GL_POLYGON);
    glVertex3f(-.7,-1.0,0.0);
    glVertex3f(-.7,-4,0.0);
    glVertex3f(.4,-2.8,0.0);
    glVertex3f(.4,-1,0);
    glEnd();
	glPopMatrix();



// BODY
    glPushMatrix();
    glColor3f(1.000, 0.753, 0.796);
    glTranslatef(-23,-13,0);
    glScalef(2.4,2,0);
    glBegin(GL_POLYGON);

    glVertex3f(1,3.5,0);
    glVertex3f(3,3.5,0);
    glVertex3f(3,-2,0);
    glVertex3f(1,-2,0);
    glEnd();
	glPopMatrix();
//frok

     glPushMatrix();
    glColor3f(1.000, 0.753, 0.796);
    glTranslatef(-23,-13,0);
    glScalef(2.4,2,0);
    glBegin(GL_POLYGON);

    glVertex3f(1,1,0);
    glVertex3f(3,1,0);
    glVertex3f(4,-1.5,0);
    glVertex3f(-.3,-1.5,0);
    glEnd();
	glPopMatrix();


//hand_y
    glPushMatrix();
    glColor3f(1.000, 0.894, 0.710);
    glTranslatef(-20,-12,0);
    glScalef(1.2,1,0);
    glBegin(GL_POLYGON);
	glVertex3f(1,3,0);
    glVertex3f(2.3,3,0);
    glVertex3f(2.3,-1,0);
    glVertex3f(1,-1,0);
    glEnd();
	glPopMatrix();

//hand_x
    glPushMatrix();
    glColor3f(1.000, 0.894, 0.710);
    glTranslatef(-18,-13,0);
    glScalef(1.2,1.4,0);
    glBegin(GL_POLYGON);
	glVertex3f(0,1,0);
    glVertex3f(4,1,0);
    glVertex3f(4,0,0);
    glVertex3f(0,0,0);
    glEnd();
	glPopMatrix();


//hand_up
    glPushMatrix();
    glColor3f(0.502, 0.000, 0.000);
    glTranslatef(-20.8,-10,0);
    glScalef(2,2,0);
    glBegin(GL_POLYGON);
	glVertex3f(.5,1,0);
    glVertex3f(2,1,0);
    glVertex3f(2,0,0);
    glVertex3f(.5,0,0);
    glEnd();
	glPopMatrix();

//leg 1
	glPushMatrix();
    glColor3f(0.412, 0.412, 0.412);
    glTranslatef(-18,-1,0);
    glScalef(1.6,2.6,3);
    glBegin(GL_POLYGON);
    glVertex3f(-1.9,-5.6,0);
    glVertex3f(-1.9,-8.6,0);
    glVertex3f(-1.0,-8.6,0);
    glVertex3f(-0.0,-5.6,0);

    glEnd();
	glPopMatrix();
//leg 2
	glPushMatrix();
    glColor3f(0.412, 0.412, 0.412);
    glTranslatef(-18,-1,0);
    glScalef(1.6,2.6,3);
    glBegin(GL_POLYGON);
    glVertex3f(-0.2,-5.6,0);
    glVertex3f(-0.0,-8.6,0);
    glVertex3f(0.9,-8.6,0);
    glVertex3f(1.5,-5.6,0);

    glEnd();
	glPopMatrix();

//feet 1
    glPushMatrix();
    glColor3f(0.412, 0.412, 0.412);
    glTranslatef(-18,-1,0);
    glScalef(1.6,2.6,3);
    glBegin(GL_POLYGON);
    glVertex3f(-0.9,-8.0,0);
    glVertex3f(-1.0,-8.6,0);
    glVertex3f(-.1,-8.6,0);
    glVertex3f(-0.9,-8,0);


    glEnd();
	glPopMatrix();

//feet 2
    glPushMatrix();
    glColor3f(0.412, 0.412, 0.412);
    glTranslatef(-18,-1,0);
    glScalef(1.6,2.6,3);
    glBegin(GL_POLYGON);
    glVertex3f(1.0,-8.0,0);
    glVertex3f(0.9,-8.6,0);
    glVertex3f(1.8,-8.6,0);
    glVertex3f(1.0,-8.0,0);


    glEnd();
	glPopMatrix();
}


void marry_go_round()
{


       glPushMatrix();
       glPopMatrix();


//filler1

       glPushMatrix();
      glColor3f(0.545, 0.271, 0.075);
      glTranslatef(-2,0,0);
      //glScalef(1.6,2.6,3);
	  glBegin(GL_POLYGON);
      glVertex3f (27, 17, 0);
      glColor3f(0.647, 0.165, 0.165);
      glVertex3f (25.5, 17, 0);
      glVertex3f (25.5, -27, 0);
      glVertex3f (27, -27, 0);
	  glEnd();
      glPopMatrix();

             //chakti
    glPushMatrix();
	glScalef(25,25,0);
	glTranslatef(1.1,.7,0);
	drawWheel();
	glPopMatrix();

	//filler2
      glPushMatrix();
	  glColor3f (0.545, 0.271, 0.075);
	  glTranslatef(-2,0,0);
	  glBegin(GL_POLYGON);
      glVertex3f (31, 16, 0);
      glVertex3f (29.5, 16, 0);
      glColor3f(0.647, 0.165, 0.165);
      glVertex3f (29.5, -30, 0);
      glVertex3f (31, -30, 0);
      glEnd();
      glPopMatrix();




///box1

      glPushMatrix();
      glColor3f(0.545, 0.271, 0.075);

      glTranslatef(3,10,0);
      glScalef(1,.5,0);
      glBegin(GL_POLYGON);
      glVertex3f (6, 12, 0);
      glVertex3f (-4, 12, 0);
      glVertex3f (-4, -2, 0);
      glVertex3f (6, -2, 0);
      glEnd();
      glPopMatrix();

      glPushMatrix();
	glColor3f(1 , 1 , 1);
	glTranslatef(3,9.5,0);
	glScalef(1,.5,0);
	  glBegin(GL_POLYGON);
      glVertex3f (5.2, 11.0, 0);
      glVertex3f (-3.2, 11.0, 0);
      glVertex3f (-3.2, 8, 0);
      glVertex3f (5.2, 8, 0);
	 glEnd();
     glPopMatrix();


   //boxx2

   glPushMatrix();
      glColor3f(0.545, 0.271, 0.075);

      glTranslatef(50,10,0);
      glScalef(1,.5,0);
      glBegin(GL_POLYGON);
      glVertex3f (6, 12, 0);
      glVertex3f (-4, 12, 0);
      glVertex3f (-4, -2, 0);
      glVertex3f (6, -2, 0);
      glEnd();
      glPopMatrix();

      glPushMatrix();
	glColor3f(1 , 1 , 1);
	glTranslatef(50,9.5,0);
	glScalef(1,.5,0);
	  glBegin(GL_POLYGON);
      glVertex3f (5.2, 11.0, 0);
      glVertex3f (-3.2, 11.0, 0);
      glVertex3f (-3.2, 8, 0);
      glVertex3f (5.2, 8, 0);
	 glEnd();
     glPopMatrix();


/// box 3
     glPushMatrix();
      glColor3f(0.545, 0.271, 0.075);

      glTranslatef(45,30,0);
      glScalef(1,.5,0);
      glBegin(GL_POLYGON);
      glVertex3f (6, 12, 0);
      glVertex3f (-4, 12, 0);
      glVertex3f (-4, -2, 0);
      glVertex3f (6, -2, 0);
      glEnd();
      glPopMatrix();

      glPushMatrix();
	glColor3f(1 , 1 , 1);
	glTranslatef(45,29.5,0);
	glScalef(1,.5,0);
	  glBegin(GL_POLYGON);
      glVertex3f (5.2, 11.0, 0);
      glVertex3f (-3.2, 11.0, 0);
      glVertex3f (-3.2, 8, 0);
      glVertex3f (5.2, 8, 0);
	 glEnd();
     glPopMatrix();


     /// box 4
     glPushMatrix();
      glColor3f(0.545, 0.271, 0.075);

      glTranslatef(8,30,0);
      glScalef(1,.5,0);
      glBegin(GL_POLYGON);
      glVertex3f (6, 12, 0);
      glVertex3f (-4, 12, 0);
      glVertex3f (-4, -2, 0);
      glVertex3f (6, -2, 0);
      glEnd();
      glPopMatrix();

      glPushMatrix();
	glColor3f(1 , 1 , 1);
	glTranslatef(8,29.5,0);
	glScalef(1,.5,0);
	  glBegin(GL_POLYGON);
      glVertex3f (5.2, 11.0, 0);
      glVertex3f (-3.2, 11.0, 0);
      glVertex3f (-3.2, 8, 0);
      glVertex3f (5.2, 8, 0);
	 glEnd();
     glPopMatrix();


     /// box 5
     glPushMatrix();
      glColor3f(0.545, 0.271, 0.075);

      glTranslatef(11,-5,0);
      glScalef(1,.5,0);
      glBegin(GL_POLYGON);
      glVertex3f (6, 12, 0);
      glVertex3f (-4, 12, 0);
      glVertex3f (-4, -2, 0);
      glVertex3f (6, -2, 0);
      glEnd();
      glPopMatrix();

      glPushMatrix();
	glColor3f(1 , 1 , 1);
	glTranslatef(11,-5,0);
	glScalef(1,.5,0);
	  glBegin(GL_POLYGON);
      glVertex3f (5.2, 11.0, 0);
      glVertex3f (-3.2, 11.0, 0);
      glVertex3f (-3.2, 8, 0);
      glVertex3f (5.2, 8, 0);
	 glEnd();
     glPopMatrix();


/// box 6
     glPushMatrix();
      glColor3f(0.545, 0.271, 0.075);

      glTranslatef(42,-5,0);
      glScalef(1,.5,0);
      glBegin(GL_POLYGON);
      glVertex3f (6, 12, 0);
      glVertex3f (-4, 12, 0);
      glVertex3f (-4, -2, 0);
      glVertex3f (6, -2, 0);
      glEnd();
      glPopMatrix();

      glPushMatrix();
	glColor3f(1 , 1 , 1);
	glTranslatef(42,-5,0);
	glScalef(1,.5,0);
	  glBegin(GL_POLYGON);
      glVertex3f (5.2, 11.0, 0);
      glVertex3f (-3.2, 11.0, 0);
      glVertex3f (-3.2, 8, 0);
      glVertex3f (5.2, 8, 0);
	 glEnd();
     glPopMatrix();



}

void balloons_stick()

{

// triangle_1
    glPushMatrix();
    glColor3f(0.545, 0.271, 0.075);
    glTranslatef(28.8,3.4,0);
    glScalef(4,2,0);
    glBegin(GL_POLYGON);
    glVertex3f(-2.7,1.1,0.0);
    glVertex3f(-0.2,-2,0.0);
    glVertex3f(2.7,1.1,0.0);
    glEnd();
    glPopMatrix();

 // triangle_2
    glPushMatrix();
    glColor3f(0.196, 0.804, 0.196);
    glTranslatef(28.8,3.4,0);
    glScalef(2.7,1.4,0);
    glBegin(GL_POLYGON);
    glVertex3f(-2.7,1.1,0.0);
    glVertex3f(-0.2,-2,0.0);
    glVertex3f(2.7,1.1,0.0);
    glEnd();
    glPopMatrix();


//khuti

 glPushMatrix();
	  glColor3f (0.545, 0.271, 0.075);
	  glTranslatef(-2,-4,0);
	  glScalef(1,.6,0);
	  glBegin(GL_POLYGON);
      glVertex3f (31, 16, 0);
      glVertex3f (29.5, 16, 0);
      glColor3f(0.647, 0.165, 0.165);
      glVertex3f (29.5, -30, 0);
      glVertex3f (31, -30, 0);
      glEnd();
      glPopMatrix();

}


void ballon()
{
   //ballon1
   glPushMatrix();
   glColor3f(1.000, 0.000, 0.000);
   glTranslatef(-18,0,0);
   glScalef(2,4,0);
   circle(3);
   glPopMatrix();
    // triangle
    glPushMatrix();
    glColor3f(1.000, 0.000, 0.000);
    glTranslatef(-18,-4,0);
    glScalef(2,3,3);
    glBegin(GL_POLYGON);
    glVertex3f(-2.7,1.1,0.0);
    glVertex3f(-0.2,-6.4,0.0);
    glVertex3f(2.7,1.1,0.0);
    glEnd();
    glPopMatrix();

// Line
    glPushMatrix();
    glColor3f(1.000, 0.000, 0.000);
    glTranslatef(-18,-4,0);
    glScalef(2,2.6,3);
    glBegin(GL_LINES);
    glVertex3f(-0.2,-6.4,0.0);
    glVertex3f(-0.2,-10.4,0.0);
    glEnd();
    glPopMatrix();
//ballon2
   glPushMatrix();
   glColor3f(0.000, 0.000, 1.000);
   glTranslatef(-10,0,0);
   glScalef(2,2.4,0);
   //glRotatef(45,0,0,0);
   circle(3);
   glPopMatrix();
// triangle
    glPushMatrix();
    glColor3f(0.000, 0.000, 0.502);
    glTranslatef(-10,-4,0);
    glScalef(2.3,2.6,3);
   // glRotatef(60,0,0,0);
    glBegin(GL_POLYGON);
    glVertex3f(-2.7,1.1,0.0);
    glColor3f(0.000, 0.000, 0.804);

    glVertex3f(-0.2,-6.4,0.0);
    glColor3f(0.000, 0.000, 1.000);

    glVertex3f(2.7,1.1,0.0);
    glEnd();
    glPopMatrix();

// Line
    glPushMatrix();
    glColor3f(1.000, 0.000, 0.000);
    glTranslatef(-10,-4,0);
    glScalef(2,2.6,3);
    //glRotatef(45,0,0,0);
    glBegin(GL_LINES);
    glVertex3f(-0.2,-6.4,0.0);
    glVertex3f(-0.2,-10.4,0.0);
    glEnd();
    glPopMatrix();
//ballon3
   glPushMatrix();
   glColor3f(0.180, 0.545, 0.341);
   glTranslatef(-24,0,0);
   glScalef(2,2.4,0);
   //glRotatef(45,0,0,0);
   circle(3);
   glPopMatrix();
// triangle
    glPushMatrix();
    glColor3f(0.000, 0.392, 0.000);
    glTranslatef(-24,-4,0);
    glScalef(2.3,2.6,3);
   // glRotatef(60,0,0,0);
    glBegin(GL_POLYGON);
    glColor3f(0.180, 0.545, 0.341);
    glVertex3f(-2.7,1.1,0.0);
    glColor3f(0.133, 0.545, 0.133);
    glVertex3f(-0.2,-6.4,0.0);
    glColor3f(0.000, 0.502, 0.000);
    glVertex3f(2.7,1.1,0.0);
    glEnd();
    glPopMatrix();

// Line
    glPushMatrix();
    glColor3f(0.000, 0.392, 0.000);
    glTranslatef(-24,-4,0);
    glScalef(2,2.6,3);
    //glRotatef(45,0,0,0);
    glBegin(GL_LINES);
    glVertex3f(-0.2,-6.4,0.0);
    glVertex3f(-0.2,-10.4,0.0);
    glEnd();
    glPopMatrix();

}
void ballon2()

{
    glPushMatrix();
   glColor3f(0.482, 0.408, 0.933);
   glTranslatef(20,-15,0);
   glRotated(45,-30,-30,-30);
   glScalef(1.5,1,0);
   ballon();
   glEnd();
   glPopMatrix();
}




void shop()
{
    // roof
    glPushMatrix();
    glColor3f(1.000, 0.871, 0.678);
    glTranslatef(25,0,0);
    glScalef(4.5,2.5,0);
    glBegin(GL_POLYGON);
    glVertex3f(0,0,0.0);
    glVertex3f(.2,1,0.0);
    glVertex3f(3.6,1,0.0);
    glVertex3f(3.8,0,0.0);
    glEnd();
    glPopMatrix();

    //ractangle

    glPushMatrix();
    glColor3f(0.000, 0.502, 0.502);
    glTranslatef(20,0,0);
    glScalef(3.5,3.5,0);
    glBegin(GL_POLYGON);
    glVertex3f(2,0,0.0);
    glVertex3f(2,-3.2,0.0);
    glVertex3f(6,-3.2,0.0);
    glVertex3f(6,0,0.0);
    glEnd();
    glPopMatrix();
    // under

    glPushMatrix();
    glColor3f(0, 0.000,0);
    glTranslatef(25,-12,0);
    glScalef(4.5,2.5,0);
    glBegin(GL_POLYGON);
    glVertex3f(0.2,0,0.0);
    glVertex3f(.2,1,0.0);
    glVertex3f(3.8,1,0.0);
    glVertex3f(3.8,0,0.0);
    glEnd();
    glPopMatrix();


}



void signal()
{
        glPushMatrix();
        glTranslatef(5,-30,0);
        glScalef(6,6,1);
    	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POLYGON);
		glVertex2f(10.6,1.6);
		glVertex2f(10.6,3.5);
		glVertex2f(10.7,3.5);
		glVertex2f(10.7,1.6);
	glEnd();


	glColor3f(0.7,0.7,0.7);
	glBegin(GL_POLYGON);
		glVertex2f(10.4,3.5);
		glVertex2f(10.4,5.0);
		glVertex2f(10.9,5.0);
		glVertex2f(10.9,3.5);
	glEnd();
	glPopMatrix();

    glPushMatrix();
    glTranslatef(68.88,-1.2,0);
    glColor3f(1,0.0,0.0);
	circle(1);
	glPopMatrix();

    glPushMatrix();
    glTranslatef(68.88,-4,0);
    glColor3f(1,1,0.0);
	circle(1);
	glPopMatrix();

    glPushMatrix();
    glTranslatef(68.88,-6.8,0);
    glColor3f(0.0,1,0.0);
	circle(1);
	glPopMatrix();
}

void a()                                        //mini Cloud

{
    //left

    glPushMatrix();
    glTranslatef(4,5.5,0);
    circle(4);
    glPopMatrix();

    //right

    glPushMatrix();
    glTranslatef(-8,5.5,0);
    circle(3.5);
    glPopMatrix();

    //top left

    glPushMatrix();
    glTranslatef(-3.5,9,0);
    circle(3.5);
    glPopMatrix();

    //top right

    glPushMatrix();
    glTranslatef(1,9,0);
    circle(3);
    glPopMatrix();

    //middle

    glPushMatrix();
    glTranslatef(-1.5,5.5,0);
    circle(4);
    glPopMatrix();

}
void tree2()

{
    glColor3f(.52,0.37,0.26);
    glTranslatef(-15,-13,0);

    glBegin(GL_POLYGON);
    glVertex3f(-3,0,0);
    glVertex3f(-10,0,0);
    glVertex3f(-9,2,0);
    glVertex3f(-4,2,0);

    glEnd();

    glBegin(GL_POLYGON);
    glVertex3f(-9,2,0);
    glVertex3f(-9,20,0);
    glVertex3f(-4,20,0);
    glVertex3f(-4,2,0);

    glEnd();
    glBegin(GL_POLYGON);
    glVertex3f(-9,20,0);
    glVertex3f(-10.5,25,0);
    glVertex3f(-2.5,25,0);
    glVertex3f(-4,20,0);

    glEnd();

    //left
glPushMatrix();
 glColor3f (0, 1 ,0);
 glTranslatef(-2,25,0);
 circle(4);
 glPopMatrix();

 //right

 glPushMatrix();
 glColor3f (0, 1 ,0);
 glTranslatef(-7,28,0);
 circle(5);
 glPopMatrix();

 //top left

 glPushMatrix();
 glColor3f (0,1,0);
 glTranslatef(-6,36,0);
 circle(5);
 glPopMatrix();

 //top right

 glPushMatrix();
 glColor3f (0, 1 ,0);
 glTranslatef(0,35,0);
 circle(5);
 glPopMatrix();

 //middle

 glPushMatrix();

 glColor3f (0, 1 ,0);
 glTranslatef(2,30.5,0);
 circle(5);
 glPopMatrix();

 glPushMatrix();
 glColor3f (0, 1 ,0);
 glTranslatef(-12.5,33,0);
 circle(5);
 glPopMatrix();

 glPushMatrix();
 glColor3f (0, 1,0);
 glTranslatef(-10,28,0);
 circle(5);
 glPopMatrix();
 glEnd();

}
void co()                                        //One Single Cloud
{
    glPushMatrix();
    glColor3f (1,1,1);
    glTranslatef(35,10,0);
    a();
    glPopMatrix();


    glPushMatrix();
    glColor3f (1,1,1);
    glTranslatef(28,16,0);
    a();
    glPopMatrix();

    glPushMatrix();
    glColor3f (1,1,1);
    glTranslatef(20,10,0);
    a();
    glPopMatrix();
}

void cloud1()
{
    glPushMatrix();
    glTranslatef(-15.0,30.0,0.0);
    glScalef(0.7,0.7,0.0);
    co();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(20.0,25.0,0.0);
    glScalef(0.7,0.7,0.0);
    co();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-60.0,25.0,0.0);
    glScalef(0.7,0.7,0.0);
    co();
    glPopMatrix();
}
void tree1()                             //green leaves
{
    glPushMatrix();
    glTranslatef(35,10,0);
    a();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(28,16,0);
    a();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(20,10,0);
    a();
    glPopMatrix();
}
void treebody()                         //tree body
{
    glBegin(GL_POLYGON);
    glColor3f (0.502, 0.000, 0.000);
    glVertex3f(0,0,0);
    glVertex3f(2.5,2,0);
    glVertex3f(4.0,-2,0);
    glVertex3f(1,-4,0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f (0.502, 0.000, 0.000);
    glVertex3f(7,2,0);
    glVertex3f(9,2,0);
    glVertex3f(8,-2,0);
    glVertex3f(4,-2,0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f (0.502, 0.000, 0.000);
    glVertex3f(1,-4,0);
    glVertex3f(4,-2,0);
    glVertex3f(8,-2,0);
    glVertex3f(7,-7,0);
    glVertex3f(1.5,-7,0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f (0.502, 0.000, 0.000);
    glVertex3f(1.5,-7,0);
    glVertex3f(7,-7,0);
    glVertex3f(6.5,-10,0);
    glVertex3f(2,-10,0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f (0.502, 0.000, 0.000);
    glVertex3f(2,-10,0);
    glVertex3f(6.5,-10,0);
    glVertex3f(6.8,-13,0);
    glVertex3f(1.5,-13,0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f (0.502, 0.000, 0.000);
    glVertex3f(1.5,-13,0);
    glVertex3f(6.8,-13,0);
    glVertex3f(7,-18,0);
    glVertex3f(.5,-18,0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f (0.502, 0.000, 0.000);
    glVertex3f(.5,-18,0);
    glVertex3f(7,-18,0);
    glVertex3f(3,-27,0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f (0.502, 0.000, 0.000);
    glVertex3f(.5,-18,0);
    glVertex3f(2.5,-23,0);
    glVertex3f(-1,-25,0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f (0.502, 0.000, 0.000);
    glVertex3f(7,-18,0);
    glVertex3f(8,-28,0);
    glVertex3f(4,-22,0);
    glEnd();
}


/****************************************************final thing add*******************************/

void car()
{

    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.52, 0.2, 0);
    glVertex3f(-0.9, 0.2, 0);
    glVertex3f(-0.87, 0.5, 0);
    glVertex3f(-0.52, 0.5, 0);
    glEnd();

    glColor3f(1.0, 0.5, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.43, 0.2, 0);
    glVertex3f(-0.52, 0.2, 0);
    glVertex3f(-0.52, 0.5, 0);
    glVertex3f(-0.46, 0.45, 0);
    glEnd();

    glColor3f(1.0, 0.5, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.53, 0.5, 0);
    glVertex3f(-0.83, 0.5, 0);
    glVertex3f(-0.77, 0.8, 0);
    glVertex3f(-0.56, 0.75, 0);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(-0.65, 0.2, 0);
    glVertex3f(-0.65, 0.5, 0);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(-0.65, 0.5, 0);
    glVertex3f(-0.68, 0.79, 0);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(-0.75, 0.2, 0);
    glVertex3f(-0.75, 0.5, 0);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(-0.75, 0.5, 0);
    glVertex3f(-0.77, 0.8, 0);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(-0.55, 0.2, 0);
    glVertex3f(-0.55, 0.5, 0);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(-0.55, 0.5, 0);
    glVertex3f(-0.58, 0.77, 0);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(-0.6, 0.4, 0);
    glVertex3f(-0.62, 0.4, 0);
    glEnd();

    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(-0.7, 0.4, 0);
    glVertex3f(-0.72, 0.4, 0);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);///sss
    glPushMatrix();
    glTranslatef(-.78, .2, 0);
    circle(0.06);
    glPopMatrix();

    glColor3f(0.0, 0.0, 0.0);///sss
    glPushMatrix();
    glTranslatef(-.5, .2, 0);
    circle(0.06);
    glPopMatrix();




    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(-.5, .2, 0);
    circle(0.02);
    glPopMatrix();

    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(-.78, .2, 0);
    circle(0.02);
    glPopMatrix();
}


void ballon1()
{

      glPushMatrix();
   glColor3f(1.000, 0.000, 0.000);
   glTranslatef(-18,-8,0);
   glScalef(2,4,0);
   half_circle(2.64);
   glPopMatrix();
    // triangle
    glPushMatrix();
    glColor3f(1.000, 0.000, 0.000);
    glTranslatef(-18,-10,0);
    glScalef(2,3,3);
    glBegin(GL_POLYGON);
    glVertex3f(-2.7,1.1,0.0);
    glVertex3f(-0.2,-6.4,0.0);
    glVertex3f(2.7,1.1,0.0);
    glEnd();
    glPopMatrix();

// Line
    glPushMatrix();
    glColor3f(1.000, 1.000, 1.000);
    glTranslatef(-18,8,0);
    glScalef(2,6,0);
    glBegin(GL_LINES);
    glVertex3f(-0.2,-6.4,0.0);
    glVertex3f(-0.2,-10.4,0.0);
    glEnd();
    glPopMatrix();
}








void intro()
{

char string[]="Prepared By VOID";
void *font=GLUT_BITMAP_TIMES_ROMAN_24;
int k;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(-10,0,0);
for(k=0;k<strlen(string);k++)
        glutBitmapCharacter(font,string[k]);

}


/***********************************************       TEXBOX AREA         *************************************************************/

void textbox()
{
    glColor3f(0.000, 0.000, 0.000);
	glPushMatrix();
	glTranslatef(5,-25,0);
	glBegin(GL_POLYGON);

	glVertex3f (-100, -23, 0.0);
    glVertex3f (-100,-5, 0.0);
    glVertex3f (100,-5, 0.0);
    glVertex3f (100,-23, 0.0);

    glEnd();
	glPopMatrix();
}


void text()
{

char string[]="The father fulfills her demand ";
void *font=GLUT_BITMAP_TIMES_ROMAN_24;
int k;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(-17,0,0);
for(k=0;k<strlen(string);k++)
        glutBitmapCharacter(font,string[k]);

}

/******************************************************************************Conversation*******************************************/

void text1()
{

char string[]=" Daughter: Dad let's buy a doll.";
void *font=GLUT_BITMAP_TIMES_ROMAN_24;
int k;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(0,0,0);
for(k=0;k<strlen(string);k++)
        glutBitmapCharacter(font,string[k]);

char string1[]="";
void *font1=GLUT_BITMAP_TIMES_ROMAN_24;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(0,-3,0);
for(k=0;k<strlen(string1);k++)
        glutBitmapCharacter(font1,string1[k]);

}

void text2()
{

char string[]=" Father: OK Let's go.";
void *font=GLUT_BITMAP_TIMES_ROMAN_24;
int k;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(0,0,0);
for(k=0;k<strlen(string);k++)
        glutBitmapCharacter(font,string[k]);


}

void text3()
{

char string[]=" Daughter: Dad Dad I need a Car like that.";
void *font=GLUT_BITMAP_TIMES_ROMAN_24;
int k;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(0,0,0);
for(k=0;k<strlen(string);k++)
        glutBitmapCharacter(font,string[k]);


}

void text4()
{

char string[]=" Dad: But baby we are going to buy a doll";
void *font=GLUT_BITMAP_TIMES_ROMAN_24;
int k;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(0,0,0);
for(k=0;k<strlen(string);k++)
        glutBitmapCharacter(font,string[k]);


}

void text5()
{

char string[]=" Daughter: NO!!!!!.I need it now";
void *font=GLUT_BITMAP_TIMES_ROMAN_24;
int k;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(0,0,0);
for(k=0;k<strlen(string);k++)
        glutBitmapCharacter(font,string[k]);


}

void text6()
{

char string[]=" press S button ";
void *font=GLUT_BITMAP_TIMES_ROMAN_24;
int k;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(0,0,0);
for(k=0;k<strlen(string);k++)
        glutBitmapCharacter(font,string[k]);


}

/****************************************************************** Second screen text   ***********************************/

void text6s()
{

char string[]=" press S button ";
void *font=GLUT_BITMAP_TIMES_ROMAN_24;
int k;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(0,0,0);
for(k=0;k<strlen(string);k++)
        glutBitmapCharacter(font,string[k]);


}


void text7()
{

char string[]=" Daughter: dad dad I need a Balloon like that";
void *font=GLUT_BITMAP_TIMES_ROMAN_24;
int k;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(0,0,0);
for(k=0;k<strlen(string);k++)
        glutBitmapCharacter(font,string[k]);


}

void text8()
{

char string[]=" Dad: But baby You have just bought a car";
void *font=GLUT_BITMAP_TIMES_ROMAN_24;
int k;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(0,0,0);
for(k=0;k<strlen(string);k++)
        glutBitmapCharacter(font,string[k]);


}

void text9()
{

char string[]=" Daughter: NO!!!!!.I need it now.";
void *font=GLUT_BITMAP_TIMES_ROMAN_24;
int k;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(0,0,0);
for(k=0;k<strlen(string);k++)
        glutBitmapCharacter(font,string[k]);


}

/****************************************************************** Third screen text   ***********************************/

void text6t()
{

char string[]=" press S button ";
void *font=GLUT_BITMAP_TIMES_ROMAN_24;
int k;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(0,0,0);
for(k=0;k<strlen(string);k++)
        glutBitmapCharacter(font,string[k]);


}

void text10()
{

char string[]=" Daughter: dad dad I need a necklace like that.";
void *font=GLUT_BITMAP_TIMES_ROMAN_24;
int k;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(0,0,0);
for(k=0;k<strlen(string);k++)
        glutBitmapCharacter(font,string[k]);


}


void text11()
{

char string[]=" Daughter: Why did the girl sell that instead of playing with that?";
void *font=GLUT_BITMAP_TIMES_ROMAN_24;
int k;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(0,0,0);
for(k=0;k<strlen(string);k++)
        glutBitmapCharacter(font,string[k]);


}

void text12()
{

char string[]=" Daughter: Take the balloon to play please.";
void *font=GLUT_BITMAP_TIMES_ROMAN_24;
int k;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(0,0,0);
for(k=0;k<strlen(string);k++)
        glutBitmapCharacter(font,string[k]);


}

void textlast()
{

char string[]=" After that girl realize that how much happy she is !! where another people indigent.  ";
void *font=GLUT_BITMAP_TIMES_ROMAN_24;
int k;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(-40,15,0);
for(k=0;k<strlen(string);k++)
        glutBitmapCharacter(font,string[k]);


char string1[]=" After that girl giving All of her toys to poor girl. then her father feeling happy. ";
void *font1=GLUT_BITMAP_TIMES_ROMAN_24;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(-40,12,0);
for(k=0;k<strlen(string1);k++)
        glutBitmapCharacter(font1,string1[k]);

char string2[]=" For this reason her father offering to his daughter to buy more toys from the front ";
void *font2=GLUT_BITMAP_TIMES_ROMAN_24;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(-40,9,0);
for(k=0;k<strlen(string2);k++)
        glutBitmapCharacter(font2,string2[k]);


        char string3[]=" site shop. But girl replied no need to buy anythings. Just she want to go home ";
void *font3=GLUT_BITMAP_TIMES_ROMAN_24;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(-40,6,0);
for(k=0;k<strlen(string3);k++)
        glutBitmapCharacter(font3,string3[k]);
}

void te()
{

char string[]="THE END";
void *font=GLUT_BITMAP_TIMES_ROMAN_24;
int k;
glColor3f(1.0,1.0,1.0);
glRasterPos3f(0,0,0);
for(k=0;k<strlen(string);k++)
        glutBitmapCharacter(font,string[k]);

}
void bl()
{
	glColor3f(0.1, 0.1, 0.1);
	glPushMatrix();
	glTranslatef(0,-1,0);
	glBegin(GL_POLYGON);

	glVertex3f (-100, -100, 0.0);
    glVertex3f (-100,100, 0.0);
    glVertex3f (100,100, 0.0);
    glVertex3f (100,-100, 0.0);

    glEnd();
	glPopMatrix();
}





void display(void)

{

	glClear(GL_COLOR_BUFFER_BIT);

if(sc==0)
{
    intro();
}

if(sc==1)
{

    anim1stwin();
sky();

sun();

    glPushMatrix();
	glColor3f (1, 1 ,1);
	glTranslatef(v_cloud_r,27,0);
	cloud();
	glPopMatrix();


	glPushMatrix();
	glColor3f (1, 1 ,1);
	glTranslatef(v_cloud_l,27,0);
	cloud();
	glPopMatrix();

glPushMatrix();
ground();
glPopMatrix();
    glPushMatrix();

glTranslatef(-26, -11, 0);
    river();
glPopMatrix();




    glPushMatrix();
    glTranslatef(0,15,0);
    glScalef(1.6,1.4,0);
    road();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-26, -11, 0);
    hills();
    glPopMatrix();

     glPushMatrix();
    glTranslatef(40,6,0);
    glScalef(.5,.5,0);
    marry_go_round();
    glEnd();
    glPopMatrix();


     glPushMatrix();
     glTranslatef(0,19,0);
     tree();
     glPopMatrix();


    glPushMatrix();
    glTranslatef(-20,10,0);
    tree();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-78,16,0);
    tree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0,-12,0);
    glScalef(0.5,0.5,0);
    house();
    glPopMatrix();
    /*glPushMatrix();
	glTranslatef(-11.45, 32.4, 0);
	glScalef(6,6,0);
	bird();
	glPopMatrix();
    glPushMatrix();
	glTranslatef(-6.45, 32.4, 0);
	glScalef(6,6,0);
	bird();
	glPopMatrix();
	 glPushMatrix();
	glTranslatef(-1.45, 32.4, 0);
	glScalef(6,6,0);
	bird();
	glPopMatrix();*/


	glPushMatrix();
	glColor3f (1, 1 ,1);
	glTranslatef(v_cloud_r,27,0);
	cloud();
	glPopMatrix();


	glPushMatrix();
	glColor3f (1, 1 ,1);
	glTranslatef(v_cloud_l,27,0);
	cloud();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(m1,-12,0);
	glScalef(.8,.8,0);
	man();
    glPopMatrix();


    glPushMatrix();
	glTranslatef(m2,-16,0);
	glScalef(.8,.6,0);
    girl();
    glPopMatrix();



    /*glPushMatrix();
    glTranslatef(0,4,0);
    glScalef(1,1,0);
    shop();
    glEnd();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,2,0);
    glScalef(.4,.4,0);
    balloons_stick();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(17,15,0);
    glScalef(.35,.35,0);
    ballon();
    ballon2();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(26,-15,0);
    glScalef(-.6,.6,0);
    girl1();
    glEnd();
    glPopMatrix();*/

textbox();  //****************************** For conversation bellow side*******************//

    glPushMatrix();
    glTranslatef(tx1,-33,0); //Daughter:Dad let's buy a doll.
    text1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(tx2,-33,0); //Father: Ok Let's go.
    text2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(tx3,-33,0); //Daughter:dad dad I need a Car like that.
    text3();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(tx4,-33,0);  // Dad:But baby we are going to buy a doll.
    text4();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(tx5,-33,0); // press Enter
    text5();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(tx6,-33,0); // press Enter
    text6();
    glPopMatrix();



}
if(sc==2)
{
    bl();
    text();
}
if(sc==3)
{

anim2ndwin();
   sky();
sun();
glPushMatrix();
ground();
glPopMatrix();



    glPushMatrix();
    glTranslatef(-26, -11, 0);


    hills();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-75,6,0);
    glScalef(.5,.5,0);
    marry_go_round();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0,15,0);
    glScalef(1.6,1.4,0);
    road();
glPopMatrix();


	glPushMatrix();
	glColor3f (1, 1 ,1);
	glTranslatef(v_cloud_r,27,0);
	cloud();
	glPopMatrix();



	glPushMatrix();
	glColor3f (1, 1 ,1);
	glTranslatef(v_cloud_l,27,0);
	cloud();
	glPopMatrix();

glPushMatrix();
    glColor3f(0.133, 0.545, 0.133);
    glTranslatef(32.0,-11.3,0.0);
    glScalef(0.4,0.5,0.0);
    tree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(40.4,-5.4,0.0);
    glScalef(0.4,0.5,0.0);
    treebody();
   glPopMatrix();

	glPushMatrix();
	glTranslatef(n1,-12,0);
	glScalef(.8,.8,0);
	man();
    glPopMatrix();


    glPushMatrix();
	glTranslatef(n2,-16,0);
	glScalef(.8,.6,0);
    girl();
    glPopMatrix();




    glPushMatrix();
    glTranslatef(c,-25,0);
    glScalef(10,2.5,0);
    car();
    glPopMatrix();





    glPushMatrix();
    glColor3f(0.133, 0.545, 0.133);
    glTranslatef(-49.0,9.5,0.0);
    glScalef(0.4,0.5,0.0);
    tree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-40.4,15.4,0.0);
    glScalef(0.4,0.5,0.0);
    treebody();
    glPopMatrix();

        glPushMatrix();
    glColor3f(0.133, 0.545, 0.133);
    glTranslatef(-19.0,9.5,0.0);
    glScalef(0.4,0.5,0.0);
    tree1();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10.4,15.4,0.0);
    glScalef(0.4,0.5,0.0);
    treebody();
    glPopMatrix();



textbox();

    glPushMatrix();
    glTranslatef(tx7,-33,0); // Daughter:dad dad I need a Balloon like that.
    text7();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(tx8,-33,0); // Dad:But baby You have just bought a car.
    text8();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(tx9,-33,0); // Daughter:NO!!!!!.I need it now.
    text9();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(tx6s,-33,0); // press Enter
    text6s();
    glPopMatrix();


     glutPostRedisplay();
}
if(sc==4)
{
    bl();
    text();
}
if(sc==5)
{





anim3rdwin();
sky();
sun();
glPushMatrix();
ground();
glPopMatrix();


     glPushMatrix();
     glTranslatef(0,19,0);
     tree();
     glPopMatrix();

    glPushMatrix();
    glTranslatef(-26,-46,0);
    glScalef(13,13,0);
    pond();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-20,20,0);
    tree();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-78,16,0);
    tree();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,15,0);
    glScalef(1.6,1.4,0);
    road();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-26, -11, 0);


    hills();
    glPopMatrix();




glPushMatrix();
	glColor3f (1, 1 ,1);
	glTranslatef(v_cloud_l,-5,0);
	cloud1();
	glPopMatrix();



    glPushMatrix();
    glTranslatef(-36,-15,0);
    glScalef(-.6,.6,0);
    girl1();
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(b,0,0);
    glScalef(.5,.5,0);
    ballon1();
    glPopMatrix();


	glPushMatrix();
	glTranslatef(p1,-12,0);
	glScalef(.8,.8,0);
	man();
    glPopMatrix();


    glPushMatrix();
	glTranslatef(p2,-16,0);
	glScalef(.8,.6,0);
    girl();
    glPopMatrix();


signal();
textbox();


    glPushMatrix();
    glTranslatef(tx10,-33,0); // Daughter:NO!!!!!.I need it now.
    text10();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(tx11,-33,0); // Daughter:NO!!!!!.I need it now.
    text11();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(tx12,-33,0); // Daughter:NO!!!!!.I need it now.
    text12();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(tx6t,-33,0); // Daughter:NO!!!!!.I need it now.
    text6t();
    glPopMatrix();
}
    if(sc==6)
    {
        textlast();
    }

    if(sc==7)

    {

           q1+=0.04;
           q2+=0.04;


             sky();
             sun();
             glPushMatrix();
             ground();
             glPopMatrix();
              glPushMatrix();

            glTranslatef(-26, -11, 0);
             river();
             glPopMatrix();

     glPushMatrix();
     glTranslatef(0,19,0);
     tree();
     glPopMatrix();


    glPushMatrix();
    glTranslatef(-20,10,0);
    tree();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-78,16,0);
    tree();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0,15,0);
    glScalef(1.6,1.4,0);
    road();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-26, -11, 0);


    hills();
    glPopMatrix();

glPushMatrix();
	glColor3f (1, 1 ,1);
	glTranslatef(v_cloud_l,-5,0);
	cloud1();
	glPopMatrix();


	glPushMatrix();
	glColor3f (1, 1 ,1);
	glTranslatef(v_cloud_r,27,0);
	cloud();
	glPopMatrix();


	glPushMatrix();
	glColor3f (1, 1 ,1);
	glTranslatef(v_cloud_l,27,0);
	cloud();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(q1,-12,0);
	glScalef(.8,.8,0);
	man();
    glPopMatrix();


    glPushMatrix();
	glTranslatef(q2,-16,0);
	glScalef(.8,.6,0);
    girl();
    glPopMatrix();




textbox();

    }


	glutSwapBuffers();

}



void init(void)
{

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
    te();
	glClearColor(0.1, 0.1, 0.1, 0.0);				// Black Background

	glClearDepth(1.0f);									// Depth Buffer Setup

	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

}


void reshape (int w, int h)
{
    glViewport (0, 0, w, h);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(45.0, (GLfloat) w/(GLfloat) h, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	gluLookAt (0.0, 0.0, 100.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}


void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {

    case 's':
        sc=sc+1;
        break;

    default:
        break;
    }
}

void mouse(int btn,int state,int x,int y)
{

	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
	sc=sc+1;
    glutPostRedisplay();
	}
}


int main()
{

   glutInitDisplayMode (GLUT_DOUBLE| GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (1600,900);
   glutInitWindowPosition (0, 0);
   glutCreateWindow ("Realizing OwnSelf");
   init ();
   glutIdleFunc(spinDisplay);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMouseFunc(mouse);
   glutKeyboardFunc(keyboard);
//   glutSpecialFunc( SpecialKeyFunc );
   glutMainLoop();
   return 0;
}
