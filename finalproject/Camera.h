#pragma once
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
class Camera
{
private:
	float x;
	float y;
	float z;

	float goalX;
	float goalY;
	float goalZ;

	bool panning = false;

	float angleY; //Angle over y axis
	float angleX; //Angle over x axis
public:
	Camera();
	~Camera();
	void update();
	void forward(float distance);
	void backward(float distance);
	void left(float angle);
	void right(float angle);
	void up(float angle);
	void down(float angle);
	void panTo(float x, float y, float z);
	void moveTo(float x, float y, float z, float angleY, float angleX);
};

