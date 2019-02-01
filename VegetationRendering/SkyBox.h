#pragma once

#include "Header.h"

class SkyBox
{
private:
	GLuint skyboxVAO;
	GLuint skyboxVBO;
	GLuint cubemapTexture;
	std::vector<std::string> faces;
public:
	GLfloat * skyboxVertices;
	SkyBox();
	GLuint loadCubemap();
	GLuint GetTexture() { return cubemapTexture; }
	GLuint GetVAO() { return skyboxVAO; }
	GLuint GetVBO() { return skyboxVBO; }
	~SkyBox();
};

