#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <math.h>
#include "Model.h"


float viewingAngle = 0;
float zpos = 0;
Model square;

void display();
void timer(int d);

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glewInit();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Window");

	//Clear stuff
	glClearDepth(1.0f);
	glClearColor(0, 0, 0, 1);

	//Objs
	square.load("../cube.obj");

	//Enable stuff
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	//glEnable(GL_AUTO_NORMAL);


	GLfloat pos0[] = { 1.0,5.0,7.0,1.0 };
	GLfloat diffuse0[] = { 0.2,0.2,0.2,1.0 };
	GLfloat ambient0[] = { 0.1,0.1,0.1,1.0 };
	GLfloat specular0[] = { 1.0,1.0,1.0,1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);

	//Set projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40, 1, .01, 1000);

	//Set viewing
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(sin(viewingAngle)*10, 0, cos(viewingAngle)*10, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glutDisplayFunc(display);
	glutTimerFunc(25, timer, 0);

	glutMainLoop();

	glEnableVertexAttribArray(0);

	return 0;
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(sin(viewingAngle) * 10, zpos, cos(viewingAngle) * 10, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glColor3f(1, 1, 0);
	glutSolidCube(.5);
	//glutSolidTeapot(.5);
	/*glBegin(GL_TRIANGLES);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 1, 0);
	glEnd();*/
	square.draw();

	glutSwapBuffers();
	glFlush();
}

void timer(int a)
{
	//what's happening here? 
	glutTimerFunc(25, timer, 0);
	//a simple rotation angle increment routine
	viewingAngle += 0.01;
	zpos += .01;
	if (zpos > 10) {
		zpos = -10;
	}
	if (viewingAngle > 360)
	{
		viewingAngle -= 360;
	}
	glutPostRedisplay();
}