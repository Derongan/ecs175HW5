#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <SOIL/SOIL.h>
#include <math.h>
#include "Model.h"
#include "Scene.h"
#include "Camera.h"
Scene scene;
Camera camera;

void display();
void timer(int d);
void keyboard(unsigned char key, int x, int y);
void special(int key, int x, int y);
void reshape(int x, int y);
//
Model *wheel1;
Model *wheel2;
Model *wheel3;
Model *wheel4;

Model *california;

Model *tree;

bool running = false;
int elapsed = 0;

int start;


double speed = .4;
double wheelcirc = .7*3.141592653 * 5;

double rots = 360.0 * (speed / wheelcirc);

double decel;

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glewInit();

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Window");
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	scene.loadSkybox("TropicalSunnyDay");


	//Clear stuff
	glClearDepth(1.0f);
	glClearColor(1, 1, 1, 1);
	
	california = new Model;
	california->load("../california", "california.obj");
	california->rotateZ(90);
	california->rotateX(-90);
	california->translate(0, -.4, 0);
	california->scale = 5;
	
	scene.addModel(california);


	tree = new Model;
	tree->load("../low poly tree", "low poly tree.obj");
	tree->translate(100, -10, 100);
	scene.addModel(tree);


	//Objs
	//wheel1 = new Model;
	//wheel1->load("../car","wheel.obj");

	//wheel1->translate(0, -.2, 0);

	//wheel1->rotateX(180);

	//wheel2 = new Model(*wheel1);
	//wheel2->translate(20, 0, 0);

	//wheel3 = new Model(*wheel1);
	//wheel3->translate(0, 0, -20);
	//wheel3->rotateX(180);

	//wheel4 = new Model(*wheel3);
	//wheel4->translate(20, 0, 0);

	//scene.addModel(wheel1);
	//scene.addModel(wheel2);
	//scene.addModel(wheel3);
	//scene.addModel(wheel4);

	//Enable stuff
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


	GLfloat pos[] = { 1,1,1,1};
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	//glEnable(GL_LIGHT1);
	//glEnable(GL_AUTO_NORMAL);



	//Set projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40, 800.0/600.0, .01, 2048);

	camera.moveTo(-39, 16, -24, -.2, 2.1);


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
	gluPerspective(40, ratio, .01, 4000);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene.render();
	camera.update();
	glutSwapBuffers();
	glFlush();

	//printf("%f, %f, %f, %f, %f\n", camera.x, camera.y, camera.z, camera.angleX, camera.angleY);
}

void timer(int a)
{
	if (running && start + 10000 > glutGet(GLUT_ELAPSED_TIME)) {

		if (start + 5000 < glutGet(GLUT_ELAPSED_TIME)) {
			rots *= .95;
			speed *= .95;
		}

		double amtrot = rots;
		double amtmov = speed;

		california->rotateComponentByName("w0", amtrot, 0, 0);
		california->rotateComponentByName("w1", amtrot, 0, 0);
		california->rotateComponentByName("w2", amtrot, 0, 0);
		california->rotateComponentByName("w3", amtrot, 0, 0);

		california->translate(amtmov, 0, 0);

		camera.x += amtmov;

		//wheel1->rotateZ(-1);
		//wheel2->rotateZ(-1);
		//wheel3->rotateZ(1);
		//wheel4->rotateZ(1);

		//wheel1->translate(-.06, 0, 0);
		//wheel2->translate(-.06, 0, 0);
		//wheel3->translate(-.06, 0, 0);
		//wheel4->translate(-.06, 0, 0);
	}
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
	case ' ':
		running = true;
		start = glutGet(GLUT_ELAPSED_TIME);
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