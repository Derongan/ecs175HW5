#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <GL/glut.h>

class Model
{
public:
	std::vector<GLfloat> verticies;
	std::vector<GLfloat> normals;
	std::vector<unsigned int> faces;
	std::vector<GLubyte> colors;
	unsigned int numFaces;
	Model();
	~Model();
	bool load(const std::string& path);
	void draw();
};

