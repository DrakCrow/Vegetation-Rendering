//#include "Header.h"
//#include "SkyBox.h"
//#include "Instance.h"
//
//GLuint FirstUnusedParticle();
//void RespawnParticle(Particle &particle);
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow *window);
//
//GLuint lastUsedParticle = 0;
//GLuint nr_particles = 2000;
//std::vector<Particle> particles;
//
//const int SCR_WIDTH = 800;
//const int SCR_HEIGHT = 600;
//
//// Camera
//Camera camera(glm::vec3(5.0f, 0.0f, 5.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//GLboolean IorG = true;
//bool IfPressed = true;
//
//float deltaTime = 0.0f;
//float lastTime = 0.0f;
//int main()
//{
//	// glfw: initialize and configure
//	// ------------------------------
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
//#endif
//	// glfw window creation
//	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//	glfwMakeContextCurrent(window);
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	glfwSetCursorPosCallback(window, mouse_callback);
//	glfwSetScrollCallback(window, scroll_callback);
//
//	// tell GLFW to capture our mouse
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	// glad: load all OpenGL function pointers
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	// define the viewport dimensions
//	// glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
//	// Set up OpenGL options
//	glEnable(GL_DEPTH_TEST);
//
//	Shader RainShader("particle.vs", "particle.fs");
//	Shader SkyShader("6.1.skybox.vs", "6.1.skybox.fs");
//	
//	//Model Test("nanosuit/nanosuit.obj");
//	Model Rain("Rain_2.obj");
//
//	SkyBox skybox;
//
//	glm::mat4 *InsModel = new glm::mat4[nr_particles];
//	glm::vec4 *InsColor = new glm::vec4[nr_particles];
//
//	// Initialize all particles
//	for (GLuint i = 0; i < nr_particles; i++)
//		particles.push_back(Particle());
//	
//	SkyShader.use();
//	SkyShader.setInt("skybox", 0);
//	RainShader.use();
//	RainShader.setInt("skybox", 0);
//	
//	while (!glfwWindowShouldClose(window))
//	{
//		float currentTime = glfwGetTime();
//		deltaTime = currentTime - lastTime;
//		lastTime = currentTime;
//
//		//std::cout << "FPS :" << 1.0f / deltaTime << std::endl;
//
//		processInput(window);
//
//		glClearColor(0.38f, 0.38f, 0.38f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		RainShader.use();
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		RainShader.setMat4("projection", projection);
//		RainShader.setMat4("view", view);
//		RainShader.setVec3("cameraPos", camera.Position);
//
//		// Add new particles
//		GLuint nr_new_particles = 50;
//		for (GLuint i = 0; i < nr_new_particles; i++)
//		{
//			GLuint temp = FirstUnusedParticle();
//			//if (temp == 0)
//			//	std::cout << currentTime << std::endl;
//			RespawnParticle(particles[temp]);
//		}
//
//		// Update all particles
//		for (GLuint i = 0; i < nr_particles; i++)
//		{
//			particles[i].Life -= deltaTime;
//			if (particles[i].Life > 0.0f)
//				particles[i].vPos -= particles[i].Velocity * deltaTime;
//			glm::mat4 model;
//			model = glm::scale(model, glm::vec3(0.01f));
//			model = glm::translate(model, particles[i].vPos);
//			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//			InsModel[i] = model;
//			InsColor[i] = particles[i].Color;
//		}
//
//		Instance ins_color(InsColor, nr_particles, "vec4");
//		Instance ins_model(InsModel, nr_particles, "mat4");
//		for (GLuint i = 0; i < Rain.meshes.size(); i++)
//		{
//			ins_color.InstanceBufferData(2, Rain.meshes[i].VAO, "vec4");
//			ins_model.InstanceBufferData(3, Rain.meshes[i].VAO, "mat4");
//		}
//
//		// draw rain particless
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.GetTexture());
//		for (GLuint i = 0; i < Rain.meshes.size(); i++)
//		{
//			glBindVertexArray(Rain.meshes[i].VAO);
//			glDrawElementsInstanced(GL_TRIANGLES, Rain.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, nr_particles);
//			glBindVertexArray(0);
//		}
//
//		glBindVertexArray(0);
//
//		//std::cout << particles[0].vPos.x << " " << particles[0].vPos.y << " " << particles[0].vPos.z << std::endl;
//
//		// Draw skybox as last
//		glDepthFunc(GL_LEQUAL);
//		SkyShader.use();
//		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
//		SkyShader.setMat4("view", view);
//		SkyShader.setMat4("projection", projection);
//		// skybox cube
//		glBindVertexArray(skybox.GetVAO());
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.GetTexture());
//		glDrawArrays(GL_TRIANGLES, 0, 36);
//		glBindVertexArray(0);
//		glDepthFunc(GL_LESS);
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//	glfwTerminate();
//	return 0;
//}
//
//GLuint FirstUnusedParticle()
//{
//	// search from last used particle, this will usually return almost instantly
//	for (GLuint i = lastUsedParticle; i < nr_particles; i++)
//		if (particles[i].Life <= 0.0f)
//		{
//			lastUsedParticle = i;
//			return i;
//		}
//	// Otherwise, do a linear search
//	for(GLuint i=0;i<lastUsedParticle;i++)
//		if (particles[i].Life <= 0.0f)
//		{
//			lastUsedParticle = i;
//			return i;
//		}
//	// override first particle if all others are alive
//	lastUsedParticle = 0;
//	return 0;
//}
//
//void RespawnParticle(Particle &particle)
//{
//	GLuint random_x = rand() % 500;
//	GLuint random_z = rand() % 500;
//	GLfloat rColor = 0.5 + ((rand() % 100) / 100.0f);
//	particle.vPos = glm::vec3(random_x, 100.0f, random_z);
//	particle.Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//	particle.Life = 1.5f;
//	particle.Velocity = glm::vec3(0.0f, 100.0f, 0.0f);
//}
//
//
//void processInput(GLFWwindow *window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.ProcessKeyboard(LEFT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.ProcessKeyboard(RIGHT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && IfPressed == false)
//	{
//		IorG = !IorG;
//		IfPressed = true;
//	}
//	else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
//	{
//		IfPressed = false;
//	}
//}
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	// make sure the viewport matches the new window dimensions; note that width and 
//	// height will be significantly larger than specified on retina displays.
//	glViewport(0, 0, width, height);
//}
//
//// glfw: whenever the mouse moves, this callback is called
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
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//	camera.ProcessMouseScroll(yoffset);
//}