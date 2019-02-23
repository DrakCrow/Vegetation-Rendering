#pragma once

class SampleModel
{
private:
	unsigned int cubeVAO = 0;
	unsigned int cubeVBO = 0;
	unsigned int quadVAO = 0;
	unsigned int quadVBO = 0;
	unsigned int sphereVAO = 0;
	unsigned int indexCount;

public:
	void renderCube();
	void renderQuad();
	void renderSphere(unsigned int segments = 128);
};
