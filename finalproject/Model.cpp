#include "Model.h"



Model::Model()
{
	numFaces = 0;
}


Model::~Model()
{
}

bool Model::load(const std::string & path)
{
	std::ifstream file;

	file.open(path.c_str());

	std::string line;

	if (!file.good()) {
		printf("Failed to load\n");
		return false;
	}

	while (!file.eof()) {
		std::getline(file, line);
		if (line.substr(0,2) == "v ") { //Vertex
			std::istringstream s(line.substr(2));
			float x, y, z;
			s >> x >> y >> z;
			verticies.push_back(x);
			verticies.push_back(y);
			verticies.push_back(z);
			colors.push_back(rand()%255);
			colors.push_back(rand()%255);
			colors.push_back(rand()%255);

			printf("x: %f y: %f z: %f\n", x, y, z);
		}
		else if (line.substr(0, 2) == "vn ") {
			std::istringstream s(line.substr(2));
			float x, y, z;
			s >> x >> y >> z;
			normals.push_back(x);
			normals.push_back(y);
			normals.push_back(z);;
		}
		else if (line.substr(0, 2) == "f ") {
			std::istringstream ss(line.substr(2));

			unsigned int v;
			int num = 0;
			do {
				ss >> v;
				ss.ignore(256, ' ');
				num++;
				faces.push_back(v-1);
			} while (ss && num < 3);
			numFaces++;
		}

	}
	return true;
}

void Model::draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);						// Enable vertex arrays
	glEnableClientState(GL_COLOR_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(3, GL_UNSIGNED_BYTE, 0, colors.data());
	//glNormalPointer(GL_FLOAT, 0, normals.data());
	glVertexPointer(3, GL_FLOAT, 0, verticies.data());			// Vertex Pointer to triangle array
	glDrawElements(GL_TRIANGLES, numFaces*3, GL_UNSIGNED_INT, faces.data()); 
	//glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);						// Disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
}
