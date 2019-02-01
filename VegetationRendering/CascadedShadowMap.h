#ifndef CSM_H
#define CSM_H

#include "Header.h"

class CSM
{
private:
	unsigned int depthMapFBO;
	unsigned int *depthMap;
public:
	const int SHADOW_NUM;
	float CascadeEnd[4];
	float ShadowOrthoProjInfo[3][6];
	float HW;

	CSM();
	CSM(int width, int height);
	bool Init(int width, int height);
	void BindForWriting(unsigned int index);
	void BindForReading();
	void SetCascadeEnd(float *pro);
	void CalcOrthoProjs(glm::mat4 pView, glm::vec3 LightPos);
	~CSM() { delete[]depthMap; }
};
#endif // !CSM_H
#pragma once
