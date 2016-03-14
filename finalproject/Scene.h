#pragma once
#include "Model.h"
#include <vector>
#include <string>
#include <SOIL\SOIL.h>
class Scene
{
private:
public:
	std::vector<Model *> models;
	
	UINT SkyboxTextures[6];
	UINT ground;

	const UINT SKYFRONT = 0;
	const UINT SKYBACK = 1;
	const UINT SKYLEFT = 2;
	const UINT SKYRIGHT = 3;
	const UINT SKYUP = 4;
	const UINT SKYDOWN = 5;

	Scene();
	~Scene();

	void render();
	void renderSkyBox(float x, float y, float z, float width, float height);
	void loadSkybox(std::string name);

	void addModel(Model *m);
	void resetMaterial();
};

