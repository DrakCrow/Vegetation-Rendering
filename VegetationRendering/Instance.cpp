#include "Instance.h"

Instance::Instance(const void *data, GLuint num, std::string type)
{
	if (type == "vec2")
	{
		glGenBuffers(1, &instanceVBO);
		glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*num, data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else if (type == "vec3")
	{
		glGenBuffers(1, &instanceVBO);
		glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*num, data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else if (type == "vec4")
	{
		glGenBuffers(1, &instanceVBO);
		glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*num, data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else if (type == "mat4")
	{
		glGenBuffers(1, &instanceVBO);
		glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4)*num, data, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void Instance::InstanceBufferData(GLuint LayoutNum, GLuint VAO, std::string type)
{
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	if (type == "vec2")
	{
		glBindVertexArray(VAO);
		glEnableVertexAttribArray(LayoutNum);
		glVertexAttribPointer(LayoutNum, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
		glVertexAttribDivisor(LayoutNum, 1);
	}
	else if (type == "vec3")
	{
		glBindVertexArray(VAO);
		glEnableVertexAttribArray(LayoutNum);
		glVertexAttribPointer(LayoutNum, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glVertexAttribDivisor(LayoutNum, 1);
	}
	else if (type == "vec4")
	{
		glBindVertexArray(VAO);
		glEnableVertexAttribArray(LayoutNum);
		glVertexAttribPointer(LayoutNum, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
		glVertexAttribDivisor(LayoutNum, 1);
	}
	else if (type == "mat4")
	{
		glBindVertexArray(VAO);
		glEnableVertexAttribArray(LayoutNum + 0);
		glVertexAttribPointer(LayoutNum + 0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glEnableVertexAttribArray(LayoutNum + 1);
		glVertexAttribPointer(LayoutNum + 1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(LayoutNum + 2);
		glVertexAttribPointer(LayoutNum + 2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(LayoutNum + 3);
		glVertexAttribPointer(LayoutNum + 3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

		glVertexAttribDivisor(LayoutNum + 0, 1);
		glVertexAttribDivisor(LayoutNum + 1, 1);
		glVertexAttribDivisor(LayoutNum + 2, 1);
		glVertexAttribDivisor(LayoutNum + 3, 1);
	}
	glBindVertexArray(0);
}

Instance::~Instance()
{
}
