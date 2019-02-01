#ifndef MODEL_H_
#define MODEL_H_

#include "glad.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "stb_image.h"


#include "Mesh.h"
#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model
{
private:
	//function
	void loadModel(std::string const &path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
public:
	//model data
	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;
	bool gammaCorrection;
	//function
	Model(std::string const &path, bool gamma = false) :gammaCorrection(gamma)
	{
		loadModel(path);
	}
	void Draw(Shader shader);
};
#endif // !MODEL_H_
