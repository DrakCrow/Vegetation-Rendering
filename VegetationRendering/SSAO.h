#ifndef SSAO_H
#define SSAO_H

#include "Header.h"

class SSAO
{
public:
	unsigned int ssaoFBO;
	unsigned int ssaoBlurFBO;
	unsigned int ssaoColorBuffer;
	unsigned int ssaoColorBufferBlur;
	unsigned int noiseTexture;
	std::vector<glm::vec3> ssaoKernel;
	std::vector<glm::vec3> ssaoNoise;
	void Init(int width, int height);
	GLfloat lerp(GLfloat a, GLfloat b, GLfloat f);
};
#endif // !SSAO_H
