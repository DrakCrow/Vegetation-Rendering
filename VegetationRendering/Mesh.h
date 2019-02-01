#ifndef MESH_H_
#define MESH_H_

#include "glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

struct Vertex
{
	//position
	glm::vec3 Position;
	//normal
	glm::vec3 Normal;
	//texcoords
	glm::vec2 TexCoords;
	//tangent
	glm::vec3 Tangent;
	//bitangent
	glm::vec3 Bitangent;
};

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {
private:
	//Render data
	unsigned int VBO, EBO;
	//functions
	//initializes all the buffer objects
	void setupMesh();
public:
	unsigned int VAO;
	//Mesh data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	//function
	//constructor
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	//render the mesh
	void Draw(Shader shader);
};
#endif // !MESH_H_
