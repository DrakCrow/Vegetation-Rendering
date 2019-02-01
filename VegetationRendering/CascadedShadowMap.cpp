#include "CascadedShadowMap.h"

CSM::CSM():SHADOW_NUM(3)
{
	depthMap = new unsigned int[SHADOW_NUM];
	CascadeEnd[0] = 0.1f;
	CascadeEnd[1] = 25.0f;
	CascadeEnd[2] = 90.0f;
	CascadeEnd[3] = 100.0f;
}

CSM::CSM(int width, int height):SHADOW_NUM(3)
{
	depthMap = new unsigned int[SHADOW_NUM];
	CascadeEnd[0] = 0.1f;
	CascadeEnd[1] = 25.0f;
	CascadeEnd[2] = 90.0f;
	CascadeEnd[3] = 100.0f;
	HW = height * 1.0f / width;
}

bool CSM::Init(int width, int height)
{
	glGenFramebuffers(1, &depthMapFBO);
	glGenTextures(SHADOW_NUM, depthMap);
	for (unsigned int i = 0; i < SHADOW_NUM; i++)
	{
		glBindTexture(GL_TEXTURE_2D, depthMap[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	/*float borderColor[] = { 1.0f,1.0f,1.0f,1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);*/
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap[0], 0);
	// Disable writes to the color buffer
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (Status != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("FB error, status: 0x%x\n", Status);
		return false;
	}
	return true;
}

void CSM::BindForWriting(unsigned int index)
{
	assert(index < SHADOW_NUM);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap[index], 0);
}

void CSM::BindForReading()
{
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, depthMap[0]);
	glActiveTexture(1);
	glBindTexture(GL_TEXTURE_2D, depthMap[1]);
	glActiveTexture(2);
	glBindTexture(GL_TEXTURE_2D, depthMap[2]);
}

void CSM::SetCascadeEnd(float * pro)
{
	for (unsigned int i = 0; i <= SHADOW_NUM; i++)
	{
		assert(pro[i] != NULL);
		CascadeEnd[i] = pro[i];
	} 
}

void CSM::CalcOrthoProjs(glm::mat4 pView, glm::vec3 LightPos)
{
	// get the inverse of the view transform
	glm::mat4 CamInv = glm::inverse(pView);

	// get the light space transform
	glm::mat4 lightView = glm::lookAt(LightPos, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	float tanHalfHFOV = glm::tan(glm::radians(45.0f));
	float tanHalfVFOV = glm::tan(glm::radians(45.0f*HW));

	for (unsigned int i = 0; i < SHADOW_NUM; i++)
	{
		float xn = CascadeEnd[i] * tanHalfHFOV;
		float xf = CascadeEnd[i + 1] * tanHalfHFOV;
		float yn = CascadeEnd[i] * tanHalfVFOV;
		float yf = CascadeEnd[i + 1] * tanHalfVFOV;

		glm::vec4 frustumCorners[] = {
			// near face
			glm::vec4(xn,yn,CascadeEnd[i],1.0f),
			glm::vec4(-xn,yn,CascadeEnd[i],1.0f),
			glm::vec4(xn,-yn,CascadeEnd[i],1.0f),
			glm::vec4(-xn,-yn,CascadeEnd[i],1.0f),
			// far face
			glm::vec4(xf,yf,CascadeEnd[i + 1],1.0f),
			glm::vec4(-xf,yf,CascadeEnd[i + 1],1.0f),
			glm::vec4(xf,-yf,CascadeEnd[i + 1],1.0f),
			glm::vec4(-xf,-yf,CascadeEnd[i + 1],1.0f)
		};
		
		glm::vec4 frustumCornersL[8];
		
		float minX = std::numeric_limits<float>::max();
		float maxX = std::numeric_limits<float>::min();
		float minY = std::numeric_limits<float>::max();
		float maxY = std::numeric_limits<float>::min();
		float minZ = std::numeric_limits<float>::max();
		float maxZ = std::numeric_limits<float>::min();

		for (unsigned int j = 0; j < 8; j++)
		{
			// transform the frustum coordinate from view to world space
			glm::vec4 vW = CamInv * frustumCorners[j];
			// transform the frustum coordinate from world to light space
			frustumCornersL[j] = lightView * vW;

			minX = std::min(minX, frustumCornersL[j].x);
			maxX = std::max(maxX, frustumCornersL[j].x);
			minY = std::min(minY, frustumCornersL[j].y);
			maxY = std::min(maxY, frustumCornersL[j].y);
			minZ = std::min(minZ, frustumCornersL[j].z);
			maxZ = std::min(maxZ, frustumCornersL[j].z);
		}
		ShadowOrthoProjInfo[i][0] = maxX;
		ShadowOrthoProjInfo[i][1] =	minX;
		ShadowOrthoProjInfo[i][2] = maxY;
		ShadowOrthoProjInfo[i][3] = minY;
		ShadowOrthoProjInfo[i][4] = maxZ;
		ShadowOrthoProjInfo[i][5] = minZ;
	}
}
