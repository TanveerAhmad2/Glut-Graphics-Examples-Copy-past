#include<windows.h>
#include<gl/glut.h>
#include<gl/glu.h>
#include<gl/gl.h>

void display (void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

int main (int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 01");
	glutDisplayFunc(display);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glutMainLoop();
	return 0;
}
