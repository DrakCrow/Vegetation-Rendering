//#include "Header.h"
//#include "Instance.h"
//#include "PBR.h"
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow *window);
//unsigned int loadTexture(const char *path);
//void RenderCube();
//void renderSphere();
//
//// settings
//const unsigned int SCR_WIDTH = 1280;
//const unsigned int SCR_HEIGHT = 720;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//float lastX = 800.0f / 2.0;
//float lastY = 600.0 / 2.0;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//int main()
//{
//	// glfw: initialize and configure
//	// ------------------------------
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_SAMPLES, 4);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
//#endif
//
//														 // glfw window creation
//														 // --------------------
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//	glfwMakeContextCurrent(window);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	// tell GLFW to capture our mouse
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	// glad: load all OpenGL function pointers
//	// ---------------------------------------
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// configure global opengl state
//	// -----------------------------
//	glEnable(GL_DEPTH_TEST);
//
//	// build and compile shaders
//	// -------------------------
//	Shader shader("vertex/pbr.vs", "fragment/pbr.fs");
//
//	shader.use();
//	shader.setVec3("albedo", 0.0f, 1.0f, 0.0f);
//	shader.setFloat("ao", 1.0f);
//
//	// lights
//	// ------
//	glm::vec3 lightPositions = glm::vec3(-5.0f, 5.0f, 5.0f);
//	glm::vec3 lightColors = glm::vec3(200.0f);
//
//	// initialize static shader uniforms before rendering
//	// --------------------------------------------------
//	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//	shader.use();
//	shader.setMat4("projection", projection);
//
//	// render loop
//	// -----------
//	while (!glfwWindowShouldClose(window))
//	{
//		// per-frame time logic
//		// --------------------
//		float currentFrame = glfwGetTime();
//		deltaTime = currentFrame - lastFrame;
//		lastFrame = currentFrame;
//
//		// input
//		// -----
//		processInput(window);
//
//		// render
//		// ------
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		shader.use();
//		glm::mat4 view = camera.GetViewMatrix();
//		shader.setMat4("view", view);
//		shader.setVec3("camPos", camera.Position);
//
//		// render rows*column number of spheres with varying metallic/roughness values scaled by rows and columns respectively
//		glm::mat4 model = glm::mat4(1.0f);
//		shader.setFloat("metallic", 1.0f);
//		shader.setFloat("roughness", 0.25f);
//		shader.setMat4("model", model);
//		renderSphere();
//		shader.setVec3("lightPosition", lightPositions);
//		shader.setVec3("lightColor", lightColors);
//		model = glm::translate(model, lightPositions);
//		shader.setMat4("model", model);
//		renderSphere();
//
//		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//		// -------------------------------------------------------------------------------
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	// glfw: terminate, clearing all previously allocated GLFW resources.
//	// ------------------------------------------------------------------
//	glfwTerminate();
//	return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow *window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	float cameraSpeed = 2.5 * deltaTime;
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.ProcessKeyboard(LEFT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.ProcessKeyboard(RIGHT, deltaTime);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}
//
//
//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//	lastX = xpos;
//	lastY = ypos;
//
//	camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(yoffset);
//}
//
//
//
//// utility function for loading a 2D texture from file
//// ---------------------------------------------------
//unsigned int loadTexture(char const * path)
//{
//	unsigned int textureID;
//	glGenTextures(1, &textureID);
//
//	int width, height, nrComponents;
//	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
//	if (data)
//	{
//		GLenum format;
//		if (nrComponents == 1)
//			format = GL_RED;
//		else if (nrComponents == 3)
//			format = GL_RGB;
//		else if (nrComponents == 4)
//			format = GL_RGBA;
//
//		glBindTexture(GL_TEXTURE_2D, textureID);
//		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//		glGenerateMipmap(GL_TEXTURE_2D);
//
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		stbi_image_free(data);
//	}
//	else
//	{
//		std::cout << "Texture failed to load at path: " << path << std::endl;
//		stbi_image_free(data);
//	}
//
//	return textureID;
//}
//
//GLuint cubeVAO = 0;
//GLuint cubeVBO = 0;
//void RenderCube()
//{
//	// Initialize (if necessary)
//	if (cubeVAO == 0)
//	{
//		GLfloat vertices[] = {
//			// Back face
//			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // Bottom-left
//			0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
//			0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
//			0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,  // top-right
//			-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  // bottom-left
//			-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,// top-left
//															  // Front face
//															  -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
//															  0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // bottom-right
//															  0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // top-right
//															  0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
//															  -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // top-left
//															  -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom-left
//																												 // Left face
//																												 -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
//																												 -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-left
//																												 -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-left
//																												 -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
//																												 -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // bottom-right
//																												 -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
//																																								   // Right face
//																																								   0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
//																																								   0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
//																																								   0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right         
//																																								   0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-right
//																																								   0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // top-left
//																																								   0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left     
//																																																					// Bottom face
//																																																					-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
//																																																					0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // top-left
//																																																					0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,// bottom-left
//																																																					0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
//																																																					-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom-right
//																																																					-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
//																																																																		// Top face
//																																																																		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
//																																																																		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
//																																																																		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top-right     
//																																																																		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
//																																																																		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
//																																																																		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f // bottom-left        
//		};
//		glGenVertexArrays(1, &cubeVAO);
//		glGenBuffers(1, &cubeVBO);
//		// Fill buffer
//		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//		// Link vertex attributes
//		glBindVertexArray(cubeVAO);
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
//		glEnableVertexAttribArray(1);
//		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//		glEnableVertexAttribArray(2);
//		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//		glBindVertexArray(0);
//	}
//	// Render Cube
//	glBindVertexArray(cubeVAO);
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//	glBindVertexArray(0);
//}
//
//// -------------------------------------------------
//unsigned int sphereVAO = 0;
//unsigned int indexCount;
//void renderSphere()
//{
//	if (sphereVAO == 0)
//	{
//		glGenVertexArrays(1, &sphereVAO);
//
//		unsigned int vbo, ebo;
//		glGenBuffers(1, &vbo);
//		glGenBuffers(1, &ebo);
//
//		std::vector<glm::vec3> positions;
//		std::vector<glm::vec2> uv;
//		std::vector<glm::vec3> normals;
//		std::vector<unsigned int> indices;
//
//		const unsigned int X_SEGMENTS = 64;
//		const unsigned int Y_SEGMENTS = 64;
//		const float PI = 3.14159265359;
//		for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
//		{
//			for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
//			{
//				float xSegment = (float)x / (float)X_SEGMENTS;
//				float ySegment = (float)y / (float)Y_SEGMENTS;
//				float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
//				float yPos = std::cos(ySegment * PI);
//				float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
//
//				positions.push_back(glm::vec3(xPos, yPos, zPos));
//				uv.push_back(glm::vec2(xSegment, ySegment));
//				normals.push_back(glm::vec3(xPos, yPos, zPos));
//			}
//		}
//
//		bool oddRow = false;
//		for (int y = 0; y < Y_SEGMENTS; ++y)
//		{
//			if (!oddRow) // even rows: y == 0, y == 2; and so on
//			{
//				for (int x = 0; x <= X_SEGMENTS; ++x)
//				{
//					indices.push_back(y       * (X_SEGMENTS + 1) + x);
//					indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
//				}
//			}
//			else
//			{
//				for (int x = X_SEGMENTS; x >= 0; --x)
//				{
//					indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
//					indices.push_back(y       * (X_SEGMENTS + 1) + x);
//				}
//			}
//			oddRow = !oddRow;
//		}
//		indexCount = indices.size();
//
//		std::vector<float> data;
//		for (int i = 0; i < positions.size(); ++i)
//		{
//			data.push_back(positions[i].x);
//			data.push_back(positions[i].y);
//			data.push_back(positions[i].z);
//			if (uv.size() > 0)
//			{
//				data.push_back(uv[i].x);
//				data.push_back(uv[i].y);
//			}
//			if (normals.size() > 0)
//			{
//				data.push_back(normals[i].x);
//				data.push_back(normals[i].y);
//				data.push_back(normals[i].z);
//			}
//		}
//		glBindVertexArray(sphereVAO);
//		glBindBuffer(GL_ARRAY_BUFFER, vbo);
//		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
//		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
//		float stride = (3 + 2 + 3) * sizeof(float);
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
//		glEnableVertexAttribArray(1);
//		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
//		glEnableVertexAttribArray(2);
//		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(5 * sizeof(float)));
//	}
//
//	glBindVertexArray(sphereVAO);
//	glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
//}
