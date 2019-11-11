#include<windows.h>
#include <GL/glut.h>
 #include <stdlib.h>

static int shoulder = 0, elbow = 0,finger=0;

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	//ramie
	glPushMatrix();
	glTranslatef(-3.0, 0.0, 0.0);
	glutWireSphere(0.03, 20, 16);
	glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glPushMatrix();
	glScalef(2.0, 0.4, 1.0);
	glutWireCube(1.0);
	glPopMatrix();

	//przedramie
	glTranslatef(1.0, 0.0, 0.0);
	glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
	glTranslatef(1.0, 0.0, 0.0);
	glutWireSphere(0.03, 20, 16);
	glPushMatrix();
	glScalef(2.0, 0.4, 1.0);
	glutWireCube(1.0);
	glPopMatrix();

	//palec1
	glTranslatef(1.0, 0.0, 0.0);
	glutWireSphere(0.03, 20, 16);
	glRotatef(20, 0.0, 0.0, 1.0);
	glTranslatef(0.3, 0.2, -0.3);
	glPushMatrix();
	glScalef(0.6, 0.1, 0.3);
	glutWireCube(1.0);
	glPopMatrix();
	//paliczek1
	glTranslatef(0.3, 0.0, 0.0);
	glRotatef(-20, 0.0, 0.0, 1.0);
	glTranslatef(0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.3);
	glutWireCube(1.0);
	glPopMatrix();

	//palec2
	glTranslatef(-0.1, 0.0, 0.0);
	glRotatef(20, 0.0, 0.0, 1.0);
	glTranslatef(-0.6, -0.2, 0.3);
	glRotatef(-20, 0.0, 0.0, 1.0);
	glTranslatef(0.3, 0.2, 0);
	glPushMatrix();
	glScalef(0.6, 0.1, 0.3);
	glutWireCube(1.0);
	glPopMatrix();
	//paliczek2
	glTranslatef(0.3, 0.0, 0.0);
	glRotatef(-20, 0.0, 0.0, 1.0);
	glTranslatef(0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.3);
	glutWireCube(1.0);
	glPopMatrix();

	//palec3
	glTranslatef(-0.1, 0.0, 0.0);
	glRotatef(20, 0.0, 0.0, 1.0);
	glTranslatef(-0.3, 0.0, 0.3);
	glPushMatrix();
	glScalef(0.6, 0.1, 0.3);
	glutWireCube(1.0);
	glPopMatrix();
	//paliczek3
	glTranslatef(0.3, 0.0, 0.0);
	glRotatef(-20, 0.0, 0.0, 1.0);
	glTranslatef(0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.3);
	glutWireCube(1.0);
	glPopMatrix();

	//palec4
	glTranslatef(-0.1, 0.0, 0.0);
	glRotatef(20, 0.0, 0.0, 1.0);
	glTranslatef(-0.3, 0, 0);
	glTranslatef(-0.1, -0.4, -0.6);
	glPushMatrix();
	glScalef(0.4, 0.1, 0.4);
	glutWireCube(1.0);
	glPopMatrix();
	//paliczek4
	glTranslatef(0.2, 0.0, 0.0);
	glRotatef(20, 0.0, 0.0, 1.0);
	glTranslatef(0.1, 0.0, 0.0);
	glPushMatrix();
	glScalef(0.2, 0.1, 0.4);
	glutWireCube(1.0);
	glPopMatrix();


	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 's':
		shoulder = (shoulder + 5) % 360;
		glutPostRedisplay();
		break;
	case 'S':
		shoulder = (shoulder - 5) % 360;
		glutPostRedisplay();
		break;
	case 'e':
		elbow = (elbow + 5) % 360;
		glutPostRedisplay();
		break;
	case 'E':          elbow = (elbow - 5) % 360;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(900, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0; }
