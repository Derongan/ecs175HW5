#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::render()
{
	//glBegin(GL_LINES);
	//glVertex3f(0, 0, 0);
	//glVertex3f(0, 0, 100);
	//glEnd();
	//glBegin(GL_LINES);
	//glVertex3f(0, 0, 0);
	//glVertex3f(0, 100, 0);
	//glEnd();
	//glBegin(GL_LINES);
	//glVertex3f(0, 0, 0);
	//glVertex3f(100, 0, 0);
	//glEnd();
	renderSkyBox(0, 0, 0, 2048, 2048);
	int x = 0;
	int y = 0;
	int z = 0;
	int width = 2048;
	int height = width;
	int length = width;
	x = x - width / 2;
	y = -4;
	z = z - width / 2;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ground);
	for (int i = 0; i < 128; i++) {
		for (int j = 0; j < 128; j++) {
			glBegin(GL_QUADS);
			glNormal3f(0, 1, 0);
			glTexCoord2f(1, 1); glVertex3f(x+(i*128)+128, y, z + (j * 128) + 128);
			glNormal3f(0, 1, 0);
			glTexCoord2f(0.0f, 1); glVertex3f(x +(i*128)+128, y, z + (j * 128));
			glNormal3f(0, 1, 0);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(x+ (i * 128), y, z + (j * 128));
			glNormal3f(0, 1, 0);
			glTexCoord2f(1, 0.0f); glVertex3f(x+ (i * 128), y, z + (j * 128) + 128);
			glEnd();
		}
	}
	glDisable(GL_TEXTURE_2D);
	for (auto model = models.begin(); model != models.end(); model++) {
		(*model)->draw();
	}
}

void Scene::resetMaterial() {
	GLfloat ambdef[] = { 0.2,0.2,0.2,1 };
	GLfloat difdef[] = { 0.8,0.8,0.8,1 };
	GLfloat specdef[] = { 0,0,0,1 };
	GLfloat emdef[] = { 0,0,0,1 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambdef);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difdef);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specdef);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emdef);
}

void Scene::renderSkyBox(float x, float y, float z, float width, float height)
{
	x = x - width / 2;
	y = y - height / 2;
	z = z - width / 2;

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	//resetMaterial();


	float length = width;
	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, SkyboxTextures[SKYFRONT]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, SkyboxTextures[SKYBACK]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, SkyboxTextures[SKYLEFT]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, SkyboxTextures[SKYRIGHT]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, SkyboxTextures[SKYUP]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, SkyboxTextures[SKYDOWN]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
}

void Scene::loadSkybox(std::string name)
{
	std::string path;
	path.append("../skyboxes/");
	path.append(name);
	path.append("/");
	path.append(name);
	GLuint tex_2d = SOIL_load_OGL_texture
		(
			(path+"Front2048.png").c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
	SkyboxTextures[SKYFRONT] = tex_2d;

	tex_2d = SOIL_load_OGL_texture
		(
			(path + "Back2048.png").c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);
	SkyboxTextures[SKYBACK] = tex_2d;

	tex_2d = SOIL_load_OGL_texture
		(
			(path + "Up2048.png").c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);
	SkyboxTextures[SKYUP] = tex_2d;

	tex_2d = SOIL_load_OGL_texture
		(
			(path + "Down2048.png").c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);
	SkyboxTextures[SKYDOWN] = tex_2d;

	tex_2d = SOIL_load_OGL_texture
		(
			(path + "Left2048.png").c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);
	SkyboxTextures[SKYLEFT] = tex_2d;

	tex_2d = SOIL_load_OGL_texture
		(
			(path + "Right2048.png").c_str(),
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
			);
	SkyboxTextures[SKYRIGHT] = tex_2d;

	ground = SOIL_load_OGL_texture
		(
			"../dir.jpg",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT | SOIL_FLAG_TEXTURE_REPEATS
			);
}

void Scene::addModel(Model *m)
{
	models.push_back(m);
}
