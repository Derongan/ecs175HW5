#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <SOIL/SOIL.h>
#include <math.h>
#include "Model.h"
#include "Scene.h"
#include "Camera.h"
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
Scene scene;
Camera camera;

void display();
void timer(int d);
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void reshape(int x, int y);

Model *wheel1;
Model *wheel2;
Model *wheel3;
Model *wheel4;

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glewInit();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Window");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	glEnable(GL_TEXTURE_2D);
	scene.loadSkybox("TropicalSunnyDay");


	//Clear stuff
	glClearDepth(1.0f);
	glClearColor(1, 1, 1, 1);

	//Objs
	wheel1 = new Model;
	wheel1->load("../car","wheel.obj");

	wheel1->rotateX(180);

	wheel2 = new Model(*wheel1);
	wheel2->translate(20, 0, 0);

	wheel3 = new Model(*wheel1);
	wheel3->translate(0, 0, -20);
	wheel3->rotateX(180);

	wheel4 = new Model(*wheel3);
	wheel4->translate(20, 0, 0);

	scene.addModel(wheel1);
	scene.addModel(wheel2);
	scene.addModel(wheel3);
	scene.addModel(wheel4);

	//Enable stuff
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);

	//glEnable(GL_LIGHT1);
	//glEnable(GL_AUTO_NORMAL);



	//Set projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40, 800.0/600.0, .01, 2048);

	camera.moveTo(0, 20, 50,0,-.5);


	glutDisplayFunc(display);
	glutTimerFunc(25, timer, 0);
	glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}

void reshape(int w, int h) {
	if (h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(40, ratio, .01, 2048);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene.render();
	camera.update();

	glutSwapBuffers();
	glFlush();
}

void timer(int a)
{
	wheel1->rotateZ(-5);
	wheel2->rotateZ(-5);
	wheel3->rotateZ(5);
	wheel4->rotateZ(5);

	wheel1->translate(-1, 0, 0);
	wheel2->translate(-1, 0, 0);
	wheel3->translate(-1, 0, 0);
	wheel4->translate(-1, 0, 0);
	glutTimerFunc(25, timer, 0);
	glutPostRedisplay();
}

void keyboard(unsigned char key, int r, int d) {
	switch (key) {
	case 'w':
		camera.forward(2.0);
		break;
	case 's':
		camera.backward(2.0);
		break;
	}
	glutPostRedisplay();
}

void special(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		camera.right(.1);
		break;
	case GLUT_KEY_LEFT:
		camera.left(.1);
		break;
	case GLUT_KEY_UP:
		camera.up(.1);
		break;
	case GLUT_KEY_DOWN:
		camera.down(.1);
		break;
	}
	glutPostRedisplay();
}