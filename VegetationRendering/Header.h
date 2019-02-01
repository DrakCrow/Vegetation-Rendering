#ifndef HEADER_H
#define HEADER_H

//#include <glew.h>
#include <glad.h>
#include <glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "shader.h"
#include "Model.h"

#include <iostream>
#include <vector>
#include <random>

struct Particle {
	glm::vec3 Velocity;
	glm::vec3 vPos;
	glm::vec4 Color;
	GLfloat Life;

	Particle()
		:vPos(0.0f), Velocity(0.0f), Color(1.0f), Life(0.0f) {}
};
#endif // !HEADER_H
#pragma once
