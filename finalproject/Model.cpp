#include "Model.h"



Model::Model()
{
}

Model::Model(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


Model::~Model()
{
}

bool Model::load(const std::string & path, const std::string & name)
{
	std::ifstream file;



	file.open(path+'/'+name);

	std::string line;

	if (!file.good()) {
		printf("Failed to load\n");
		return false;
	}

	component *comp = new component;

	while (!file.eof()) {
		std::getline(file, line);
		if (line.substr(0, 2) == "g ") {
			std::istringstream ss(line.substr(2));
			std::string name;
			ss >> name;


			components.push_back(comp);

			comp = new component();
			comp->name = name;
		}
		else if (line.substr(0,2) == "v ") { //Vertex
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
		}
		else if (line.substr(0, 2) == "f ") {
			std::istringstream ss(line.substr(2));

			unsigned int v;
			int num = 0;
			do {
				ss >> v;
				ss.ignore(256, ' ');
				num++;
				comp->faces.push_back(v - 1);
				faces.push_back(v - 1);
			} while (ss && num < 3);
		}
		else if (line.substr(0, 2) == "mt") {
			std::istringstream ss(line.substr(7));
			std::string mtl;
			ss >> mtl;
			continue;
			std::ifstream mtlfile;
			mtlfile.open(path + '/' + mtl);

			while (mtlfile) {
				std::getline(mtlfile, line);
				mat *current = nullptr;
				if (line.substr(0, 2) == "ne") {
					current = new mat();
				}
				if (current != nullptr) {
					if (line.substr(0, 2) == "Ns") {
						std::istringstream ss(line.substr(2));
						float val;
						ss >> val;
						current->Ns = val;
					}
					else if (line.substr(0, 2) == "Ni") {
						std::istringstream ss(line.substr(2));
						float val;
						ss >> val;
						current->Ni = val;
					}
					else if (line.substr(0, 2) == "il") {
						std::istringstream ss(line.substr(2));
						float val;
						ss >> val;
						current->illum = val;
					}
					else if (line.substr(0, 1) == "K") {
						std::istringstream ss(line.substr(1));
						char what = ss.get();
						float x, y, z;
						ss >> x >> y >> z;
						switch (what) {
						case 'a':
							current->Ka[0] = x;
							current->Ka[1] = y;
							current->Ka[2] = z;
							break;
						case 'd':
							current->Kd[0] = x;
							current->Kd[1] = y;
							current->Kd[2] = z;
							break;
						case 's':
							current->Ks[0] = x;
							current->Ks[1] = y;
							current->Ks[2] = z;
							break;
						case 'e':
							current->Ke[0] = x;
							current->Ke[1] = y;
							current->Ke[2] = z;
							break;
						}
					}
				}
			}

			mtlfile.close();			
		}
		else if (line.substr(0, 2) == "us") {
			std::istringstream ss(line.substr(6));
			std::string mtl;
			ss >> mtl;

			printf("Using material %s\n", mtl.c_str());
		}
	}

	components.push_back(comp);

	normals.resize(verticies.size());
	for (int i = 0; i < faces.size(); i += 3) {
		//printf("%i,%i,%i\n",faces[i],faces[i+1],faces[i+2]);
		int v1 = faces[i];
		int v2 = faces[i + 1];
		int v3 = faces[i + 2];

		float ux = verticies[v1 * 3] - verticies[v3 * 3];
		float uy = verticies[v1 * 3 + 1] - verticies[v3 * 3+1];
		float uz = verticies[v1 * 3 + 2] - verticies[v3 * 3+2];

		float vx = verticies[v2 * 3] - verticies[v3 * 3];
		float vy = verticies[v2 * 3 + 1] - verticies[v3 * 3+1];
		float vz = verticies[v2 * 3 + 2] - verticies[v3 * 3+2];

		float nx = (uy*vz) - (uz*vy);
		float ny = (uz * vx) - (ux * vz);
		float nz = (ux * vy) - (uy * vx);

		//printf("%f, %f, %f", vx, vy, vz);

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

		normals[i] /= val;
		normals[i+1] /= val;
		normals[i+2] /= val;

		//printf("%f %f %f\n", normals[i], normals[i + 1], normals[i + 2]);
	}


	//Calculate bounding boxes
	for (auto c = components.begin(); c != components.end(); c++) {
		component* cx = *c;
		cx->minX = cx->minY = cx->minZ = FLT_MAX;
		cx->maxX = cx->maxY = cx->maxZ = FLT_MIN;
		for (int i = 0; i < cx->faces.size(); i++) {
			float x = verticies[cx->faces[i]*3];
			float y = verticies[cx->faces[i]*3+1];
			float z = verticies[cx->faces[i]*3+2];

			cx->maxX = fmaxf(cx->maxX, x);
			cx->maxY = fmaxf(cx->maxY, y);
			cx->maxZ = fmaxf(cx->maxZ, z);

			cx->minX = fminf(cx->minX, x);
			cx->minY = fminf(cx->minY, y);
			cx->minZ = fminf(cx->minZ, z);
		}
	}

	return true;
}

void Model::draw()
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(angleX, 1, 0, 0);
	glRotatef(angleY, 0, 1, 0);
	glRotatef(angleZ, 0, 0, 1);
	glScalef(scale, scale, scale);
	glEnableClientState(GL_VERTEX_ARRAY);						// Enable vertex arrays
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normals.data());
	glVertexPointer(3, GL_FLOAT, 0, verticies.data());			// Vertex Pointer to triangle array
	for (int i = 0; i < components.size(); i++) {
		component* c = components[i];
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		//if (c->name.compare("w0") != 0)
		//	continue;

		glPushMatrix();
		float centerX = c->minX + .34;
		float centerY = c->minY + .34;
		float centerZ = c->minZ + .34;

		//printf("%f %f %f\n", (c->maxX - c->minX) / 2, (c->maxY - c->minY) / 2, (c->maxZ - c->minZ) / 2);


		//useMat(components[i]->matName);
		glTranslatef(centerX, centerY, centerZ);
		glRotatef(components[i]->angleX, 1, 0, 0);
		glRotatef(components[i]->angleY, 0, 1, 0);
		glRotatef(components[i]->angleZ, 0, 0, 1);
		glTranslatef(-centerX, -centerY, -centerZ);
		glDrawElements(GL_TRIANGLES, components[i]->faces.size(), GL_UNSIGNED_INT, components[i]->faces.data());
		glPopMatrix();
	}
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);						// Disable vertex arrays
	glPopMatrix();
}

void Model::setPosition(float x, float y, float z, float angleY, float angleX)
{
	this->x = x;
	this->y = y;
	this->z = z;

	this->angleX = angleX;
	this->angleY = angleY;
}

void Model::rotateX(float angle)
{
	angleX += angle;
}

void Model::rotateY(float angle)
{
	angleY += angle;
}

void Model::rotateZ(float angle)
{
	angleZ += angle;
}

void Model::useMat(std::string name)
{
	for (int i = 0; i < materials.size();i++) {
		if (materials[i].name.compare(name) == 0) {
			glMaterialfv(GL_FRONT, GL_AMBIENT, materials[i].Ka.data());
			glMaterialfv(GL_FRONT, GL_DIFFUSE, materials[i].Kd.data());
			glMaterialfv(GL_FRONT, GL_SPECULAR, materials[i].Ks.data());
			glMaterialfv(GL_FRONT, GL_EMISSION, materials[i].Ke.data());
			return;
		}
	}
}

void Model::translate(float x, float y, float z)
{
	this->x += x;
	this->y += y;
	this->z += z;
}

void Model::rotateComponentByName(std::string name, float aX, float aY, float aZ)
{
	for (auto comp = components.begin(); comp != components.end(); comp++) {
		if (name.compare((*comp)->name) == 0) {
			(*comp)->angleX += aX;
			(*comp)->angleY += aY;
			(*comp)->angleZ += aZ;
			return;
		}
	}
}
