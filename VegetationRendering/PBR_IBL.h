#ifndef PBR_H

#include "Header.h"
#include "SampleModel.h"
#include "shader.h"

class PBR
{
private:
	GLfloat metallic;
	GLfloat roughness;
	
	GLuint hdrTexture;

	GLuint captureFBO;
	GLuint captureRBO;

	GLuint envCubemap;
	GLuint irradianceMap;
	GLuint prefilterMap;
	GLuint brdfLUTTexture;

	void CheckFrameBufferCompleteness(GLuint framebuffer);
	void CubeMapFrameBuffer();

public:
	// variable
	glm::mat4 captureProjection;
	glm::mat4 *captureViews;
	GLuint TextureResolution;

	SampleModel model;

	// function
	PBR(GLuint resolution = 1024, std::string filepath = " ");
	~PBR();
	bool LoadHDRImage(std::string filepath);
	void IrradianceMapFrameBuffer(GLuint resolution = 32);
	void PrefilterMapFrameBuffer(GLuint resolution = 128);
	void BrdfMapFrameBuffer(GLuint resolution = 512);
	// pbr: convert HDR equirectangular environment map to cubemap equivalent
	// ----------------------------------------------------------------------
	void EquirectangularMapToCubeMapShader(std::string vs_path, std::string fs_path);
	void IrradianceConvolution(std::string vs_path, std::string fs_path, GLuint Ir_resolution = 32);
	void PrefilterEnviromentMap(std::string vs_path, std::string fs_path, GLuint Pr_resolution = 128, GLuint MaxMip = 5);
	void BrdfLookUpTexture(std::string vs_path, std::string fs_path);

	// get variable
	GLfloat GetMaterialMetallic() { return metallic; }
	GLfloat GetMaterialRoughness() { return roughness; }

	GLuint GetPbrFrameBufferObject() { return captureFBO; }
	GLuint GetPbrRenderBufferObject() { return captureRBO; }

	GLuint GetIblHdrTexture() { return hdrTexture; }
	GLuint GetIblCubemapTexture() { return envCubemap; }
	GLuint GetIblConvolutionMapTexture() { return irradianceMap; }
	GLuint GetIblPrefilterMapTexture() { return prefilterMap; }
	GLuint GetIblBrdfLUTTexture() { return brdfLUTTexture; }
};

#endif // !PBR_H