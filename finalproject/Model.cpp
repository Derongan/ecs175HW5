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
			/*colors.push_back(rand()%255);
			colors.push_back(rand()%255);
			colors.push_back(rand()%255);*/
			colors.push_back(0);
			colors.push_back(0);
			colors.push_back(50);
		}
		else if (line.substr(0, 2) == "vn ") {
			std::istringstream s(line.substr(3));
			float x, y, z;
			s >> x >> y >> z;
			normals.push_back(x);
			normals.push_back(y);
			normals.push_back(z);
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

	normals.resize(verticies.size());
	for (int i = 0; i < faces.size(); i += 3) {
		printf("%i,%i,%i\n",faces[i],faces[i+1],faces[i+2]);
		int v1 = faces[i];
		int v2 = faces[i + 1];
		int v3 = faces[i + 2];

		float ux = verticies[v1 * 3];
		float uy = verticies[v1 * 3 + 1];
		float uz = verticies[v1 * 3 + 2];

		float vx = verticies[v2 * 3];
		float vy = verticies[v2 * 3 + 1];
		float vz = verticies[v2 * 3 + 2];

		float nx = (uy*vz) - (uz*vy);
		float ny = (uz * vx) - (ux * vz);
		float nz = (ux * vy) - (uy * vx);

		normals[v1 * 3] += nx;
		normals[v2 * 3] += nx;
		normals[v3 * 3] += nx;

		normals[v1 * 3 + 1] += ny;
		normals[v2 * 3 + 1] += ny;
		normals[v3 * 3 + 1] += ny;

		normals[v1 * 3 + 2] += nz;
		normals[v2 * 3 + 2] += nz;
		normals[v3 * 3 + 2] += nz;
	}

	for (int i = 0; i < normals.size(); i+=3) {
		float x = normals[i];
		float y = normals[i+1];
		float z = normals[i+2];

		float val = sqrt(x*x + y*y + z*z);

		/*normals[i] /= val;
		normals[i+1] /= val;
		normals[i+2] /= val;*/

		printf("%f %f %f\n", normals[i], normals[i + 1], normals[i + 2]);
	}

	return true;
}

void Model::draw()
{
	//glShadeModel(GL_SMOOTH);

	glEnableClientState(GL_VERTEX_ARRAY);						// Enable vertex arrays
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals.data());
	glVertexPointer(3, GL_FLOAT, 0, verticies.data());			// Vertex Pointer to triangle array
	glDrawElements(GL_TRIANGLES, numFaces*3, GL_UNSIGNED_INT, faces.data()); 
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);						// Disable vertex arrays
}
