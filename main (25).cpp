#include <Windows.h>
#include <GL/glut.h>
#include <stdlib.h>

constexpr GLsizei w = 600, h = 600;
constexpr GLfloat SIZE_F = 1.0f;

GLfloat angle = 0.0;
GLfloat unit = 0.0;

int op = 0;

void init() {
	glClearColor(0.0, 0.0, 0.0, 0.0); // Black BackGround
	glClearDepth(1.0f);

	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	GLfloat lightpos[] = { 10.0f,10.0f,10.0f,1.0 };
	GLfloat light0_mat1[] = { 0.2, 0.2, 0.2, 0.3 };
	GLfloat light0_diff[] = { 0.8, 0.8, 0.8, 0.3 };

	GLfloat lightpos2[] = { 6.0,8.0,6.0,1.0 };
	GLfloat light1_mat1[] = { 0.1,0.1,0.1,0.3 };
	GLfloat light1_diff[] = { 0.1,0.1,0.1,0.3 };

	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_mat1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);

	glLightfv(GL_LIGHT1, GL_POSITION, lightpos2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_mat1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diff);

	GLfloat no_mat[] = { 0.0,0.0,0.0,1.0 };
	GLfloat mat_ambient[] = { 0.2,0.2,0.2,1.0 };
	GLfloat mat_diffuse[] = { 0.8,0.8,0.8,1.0 };
	GLfloat mat_specular[] = { 0.3,0.3,0.3,1.0 };
	GLfloat high_shininess[] = { 20.0 };
	GLfloat high_mat[] = { 0.25,0.25,0.25,1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, high_mat);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// Solid Floor

	glPushMatrix();
	{
		glTranslatef(0, -2.0f, 0);
		glScalef(5, 1, 5);
		glutSolidCube(1.0);
	}
	glPopMatrix();

	// Left Wall
	glPushMatrix();
	{
		glTranslatef(-2.0f, 0, 0);
		glRotatef(90, 0, 0, 1);
		glScalef(5, 1, 5);
		glutSolidCube(1.0);
	}
	glPopMatrix();

	// Right Wall
	glPushMatrix();
	{
		glTranslatef(0, 0, -2);
		glRotatef(90, 1.0, 0.0, 0.0);
		glScalef(5, 1, 5);
		glutSolidCube(1.0);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glTranslatef(1.0, 0.0, 1.0);
		//TOP-LEFT
		glPushMatrix();
		{
			glColor3f(1.0, 1.0, 1.0);
			glTranslatef(-unit, 0, 0);
			glBegin(GL_QUADS);
			{
				glVertex3f(0.0f, 1.0f, -1.0f);
				glVertex3f(-1.0f, 1.0f, -1.0f);
				glVertex3f(-1.0f, 1.0f, 1.0f);
				glVertex3f(0.0f, 1.0f, 1.0f);
			}glEnd();
		}
		glPopMatrix();

		//TOP-RIGHT
		glPushMatrix();
		{
			glTranslatef(unit, 0, 0);
			glBegin(GL_QUADS);
			glVertex3f(0.0f, 1.0f, -1.0f);
			glVertex3f(1.0f, 1.0f, -1.0f);
			glVertex3f(1.0f, 1.0f, 1.0f);
			glVertex3f(0.0f, 1.0f, 1.0f);
			glEnd();
		}
		glPopMatrix();

		glBegin(GL_QUADS);
		{
			// Bottom
			glColor3f(1.0f, 0.5f, 0.0f);     // Orange
			glVertex3f(1.0f, -1.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(1.0f, -1.0f, -1.0f);


			// Front face  (z = 1.0f)
			glColor3f(1.0f, 0.0f, 0.0f);     // Red
			glVertex3f(1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, 1.0f);

			// Back face (z = -1.0f)
			glColor3f(1.0f, 0.5f, 0.0f);    // Yellow
			glVertex3f(1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, 1.0f, -1.0f);
			glVertex3f(1.0f, 1.0f, -1.0f);

			// Left face (x = -1.0f)
			glColor3f(1.0f, 0.5f, 0.0f);     // Blue
			glVertex3f(-1.0f, 1.0f, 1.0f);
			glVertex3f(-1.0f, 1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);

			// Right face (x = 1.0f)
			glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
			glVertex3f(1.0f, 1.0f, -1.0f);
			glVertex3f(1.0f, 1.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, 1.0f);
			glVertex3f(1.0f, -1.0f, -1.0f);
		}
		glEnd();

		glColor3f(1.0, 0.0, 0.0);
		glTranslatef(0.0, unit, 0.0);
		glRotatef(angle, 0.0, 1.0, 0.0);
		glutSolidTeapot(0.5);
	}
	glPopMatrix();


	glutSwapBuffers();
}

void reshape(GLint width, GLint height) {
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-SIZE_F, SIZE_F, -SIZE_F, SIZE_F, 2.0f, 20.0f);

	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case '1':
		op = 1;
		break;
	case '2':
		op = 2;
		break;
	case '3':
		op = 3;
		break;
	case '4':
		op = 4;
		break;
	default:
		break;
	}
}

void idle() {
	switch (op)
	{
	case 1:
		angle += 1.0;
		Sleep(15);
		break;
	case 2:
		angle -= 1.0;
		Sleep(15);
		break;
	case 3:
		if (unit < 1.0)
			unit += 0.05;
		Sleep(15);
		break;
	case 4:
		if (unit > 0.0)
			unit -= 0.05;
		Sleep(15);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(w, h);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("TEMP");

	init();
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glutMainLoop();
}
