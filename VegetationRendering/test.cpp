//#include "Header.h"
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow *window);
//void renderOct();
//
//// settings
//const unsigned int SCR_WIDTH = 1280;
//const unsigned int SCR_HEIGHT = 720;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
//float lastX = (float)SCR_WIDTH / 2.0;
//float lastY = (float)SCR_HEIGHT / 2.0;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//int level = 0;
//float radius = 1.0f;
//
//float lerp(float a, float b, float f)
//{
//	return a + f * (b - a);
//}
//
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
//	// --------------------
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
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// Ïß¿òÄ£Ê½
//
//	// build and compile shaders
//	// -------------------------¡¢¡¢
//	Shader SubShader("SphereSubdivision.vs", "SphereSubdivision.fs","SphereSubdivision.gs");
//	//Shader SubShader("SphereSubdivision.vs", "SphereSubdivision.fs");
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
//		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		// 1. geometry pass: render scene's geometry/color data into gbuffer
//		// -----------------------------------------------------------------
//		SubShader.use();
//		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 50.0f);
//		glm::mat4 view = camera.GetViewMatrix();
//		glm::mat4 model = glm::mat4(1.0f);
//		SubShader.setMat4("projection", projection);
//		SubShader.setMat4("proj", projection);
//		SubShader.setMat4("modelview", view*model);
//		SubShader.setMat4("view", view);
//		SubShader.setMat4("model", model);
//		SubShader.setInt("level", level);
//		SubShader.setFloat("radius", radius);
//		renderOct();
//
//		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//		// -------------------------------------------------------------------------------
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glfwTerminate();
//	return 0;
//}
//
//GLuint OctVAO = 0;
//GLuint OctVBO;
//void renderOct()
//{
//	if (OctVAO == 0)
//	{
//		float OctVertices[] = {
//			// positions      
//			0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f, 0.0f,1.0f,0.0f,
//			1.0f,0.0f,0.0f, 0.0f,0.0f,-1.0f, 0.0f,1.0f,0.0f,
//			0.0f,0.0f,-1.0f, -1.0f,0.0f,0.0f, 0.0f,1.0f,0.0f,
//			-1.0f,0.0f,0.0f, 0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f,
//			0.0f,0.0f,1.0f, 1.0f,0.0f,0.0f, 0.0f,-1.0f,0.0f,
//			1.0f,0.0f,0.0f, 0.0f,0.0f,-1.0f, 0.0f,-1.0f,0.0f,
//			0.0f,0.0f,-1.0f, -1.0f,0.0f,0.0f, 0.0f,-1.0f,0.0f,
//			-1.0f,0.0f,0.0f, 0.0f,0.0f,1.0f, 0.0f,-1.0f,0.0f
//		};
//		// setup plane VAO
//		glGenVertexArrays(1, &OctVAO);
//		glGenBuffers(1, &OctVBO);
//		glBindVertexArray(OctVAO);
//		glBindBuffer(GL_ARRAY_BUFFER, OctVBO);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(OctVertices), &OctVertices, GL_STATIC_DRAW);
//		glEnableVertexAttribArray(0);
//		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	}
//	glBindVertexArray(OctVAO);
//	glDrawArrays(GL_TRIANGLE_STRIP, 0, 24);
//	glBindVertexArray(0);
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ,l
//bool If_Q = false;
//bool If_E = false;
//void processInput(GLFWwindow *window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.ProcessKeyboard(FORWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.ProcessKeyboard(BACKWARD, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.ProcessKeyboard(LEFT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.ProcessKeyboard(RIGHT, deltaTime);
//	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && If_Q == false)
//	{
//		If_Q = true;
//		if (level > 0)
//			level--;
//	}
//	else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_RELEASE && If_Q == true)
//		If_Q = false;
//	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && If_E == false)
//	{
//		If_E = true;
//		if (level < 3)
//			level++;
//	}
//	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE && If_E == true)
//		If_E = false;
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