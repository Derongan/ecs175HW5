#include <GL/freeglut.h>
#include <string>
#include <math.h>
#include "Model.h"

float viewingAngle = 0;
Model square;

void display();
void timer(int d);

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Window");

	//Clear stuff
	glClearDepth(1.0f);
	glClearColor(0, 0, 0, 1);

	//Objs
	square.load("../sphere.obj");

	//Enable stuff
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);


	GLfloat diffuseParams[] = {
		1,1,1,1
	};

	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseParams);

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

	return 0;
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(sin(viewingAngle) * 10, 10, cos(viewingAngle) * 10, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glColor3f(1, 1, 0);
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
	viewingAngle += 0.1;
	if (viewingAngle > 360)
	{
		viewingAngle -= 360;
	}
	glutPostRedisplay();
}