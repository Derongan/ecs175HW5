#include "Camera.h"

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::update()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, x + sin(angleY), y + sin(angleX), z - cos(angleY), 0.0, 1.0, 0.0);
}

void Camera::forward(float distance)
{
	x += sin(angleY) * distance;
	y += sin(angleX) * distance;
	z -= cos(angleY) * distance;
}

void Camera::backward(float distance)
{
	forward(-distance);
}

void Camera::left(float angle)
{
	angleY -= angle;
}

void Camera::right(float angle)
{
	left(-angle);
}

void Camera::up(float angle)
{
	angleX += angle;
}

void Camera::down(float angle)
{
	up(-angle);
}

void Camera::panTo(float x, float y, float z)
{
	goalX = x;
	goalY = y;
	goalZ = z;
	panning = true;
}

void Camera::moveTo(float x, float y, float z, float angleX, float angleY)
{
	this->x = x;
	this->y = y;
	this->z = z;

	this->angleX = angleX;
	this->angleY = angleY;
}
