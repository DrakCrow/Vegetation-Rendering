#pragma once

#include "Header.h"

class Instance
{
private:
	GLuint instanceVBO;
public:
	Instance(const void *data = NULL, GLuint num = 100, std::string type = "vec3");
	void InstanceBufferData(GLuint LayoutNum, GLuint VAO = 0, std::string type = "vec3");
	~Instance();
};

