#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <GL/glut.h>
#include <math.h>

class Model
{
private:
	float x;
	float y;
	float z;

	float angleY;
	float angleX;
	float angleZ;

	bool bounding = true;

	typedef struct {
		std::string name;
		std::vector<GLfloat> Ka;
		std::vector<GLfloat> Kd;
		std::vector<GLfloat> Ks;
		std::vector<GLfloat> Ke;
		GLfloat Ni;
		GLfloat Ns;
		GLfloat illum;
	} mat;

	typedef struct {
		std::string matName;
		std::string name;
		std::vector<unsigned int> faces;
		float angleY;
		float angleX;
		float angleZ;

		float maxX;
		float maxY;
		float maxZ;
		float minX;
		float minY;
		float minZ;
	} component;
public:
	std::vector<GLfloat> verticies;
	std::vector<GLfloat> normals;
	std::vector<GLfloat> textures;
	std::vector<unsigned int> faces;
	std::vector<GLubyte> colors;
	std::vector<component*> components;
	std::vector<mat> materials;
	float scale = 1;
	Model();
	Model(float x, float y, float z);
	~Model();
	bool load(const std::string& path, const std::string& name);
	void draw();
	void setPosition(float x, float y, float z, float angleY, float angleX);
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	void useMat(std::string name);
	void translate(float x, float y, float z);

	void rotateComponentByName(std::string name, float aX, float aY, float aZ);
};

