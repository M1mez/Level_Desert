#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "forwardDeclaration.h"
#include <vector>
#include "Camera.h"
#include "model.h"
#include "helperFunctions.h"
#include <ctime>

#define PRINTER(name, size) std::cout << #name << ":  " << size << std::endl;

// window / monitor
GLFWwindow* window = nullptr;
GLFWmonitor* primaryMonitor;
const GLFWvidmode* primaryMode;
int SCR_WIDTH = 1024;
int SCR_HEIGHT = 768;
bool isFullScreen = false;

// objects
Mesh *disk;
Mesh *glass;
std::vector<Model*> cactusModels;
std::pair<std::vector<glm::vec2>, std::vector<float>> cactusLocAndRot;
const float LOD_NEAR = 25.0f;
const float LOD_MID = 75.0f;
const int OBJECTS_AMOUNT = 50;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float max_altitude = 15.0f;
float min_altitude = 0.2f;
const float drawDistance = 250.0f;

glm::mat4 projection;
glm::mat4 view;
glm::mat4 model;

// world
float planeRadius = 100.0f;
float playerBounds = planeRadius - (planeRadius / 10.0f);
bool playerBound = true;
float playerSpeed = 10.5f;

// timing
float currentFrame;
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int initializeGL();
int mainLoop();
void processInput(GLFWwindow *window);
void cleanUp();
void monitorWork();
void switchFullScreen(void);

int main()
{
	srand(time(NULL));
	if (initializeGL() < 0) return -1;

	initializeMaps();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (mainLoop() < 0) return -1;


	cleanUp();
	return 0;
}

int mainLoop()
{
	//create OBJECTS_AMOUNT valid locations with distance to each other of minDist
	createLocations(OBJECTS_AMOUNT, cactusLocAndRot.first, 7.5f);
	PRINTER(cactusLocAndRot, cactusLocAndRot.first.size());

	//create randomrotation for each object location
	for (unsigned int i = 0; i < cactusLocAndRot.first.size(); i++) cactusLocAndRot.second.push_back(randomFloatBetween(0.0f, 360.0f));

	//create all needed models
	createCactus(cactusModels);
	createScenery();

	while (!glfwWindowShouldClose(window))
	{
		//get current timeframe
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//keypresses and mouse
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		// view / projection transformations
		projection = glm::perspective(glm::radians(camera.Zoom), static_cast<float>(SCR_WIDTH) / static_cast<float>(SCR_HEIGHT), 0.1f, drawDistance);
		view = camera.GetViewMatrix();

		//set plane.y so that camera is above plane
		float planeOffsetY = -2.5f;
		model = glm::translate(model, glm::vec3(0.0f, planeOffsetY, 0.0f));

#pragma region plane
		disk->shader->use();
		disk->setMat4("projection", projection);
		disk->setMat4("view", view);
		disk->setMat4("model", model);
		disk->Draw();
#pragma endregion

#pragma region generic objects
		for (unsigned int index = 0; index < cactusLocAndRot.first.size(); index++) {
			auto loc = cactusLocAndRot.first[index];
			const float distance = getDistance(glm::vec2(camera.Position.x, camera.Position.z), loc);

			if		(distance <= LOD_NEAR)	cactusModels[0]->Draw(model, projection, view, cactusLocAndRot.second[index], glm::vec3(loc.x, 0.0f, loc.y));
			else if (distance >= LOD_MID)	cactusModels[2]->Draw(model, projection, view, cactusLocAndRot.second[index], glm::vec3(loc.x, 0.0f, loc.y));
			else							cactusModels[1]->Draw(model, projection, view, cactusLocAndRot.second[index], glm::vec3(loc.x, 0.0f, loc.y)); }
#pragma endregion

#pragma region glass wall
		drawGlass(model, projection, view, camera.Position);
#pragma endregion

		drawCameraLenses(model, projection, view, camera.Position);


		//reset plane.y
		model = glm::translate(model, glm::vec3(0.0f, -planeOffsetY, 0.0f));

#pragma region skybox
		// remove translation from the view matrix, so skybox is always same distance
		drawSkyBox(model, projection, glm::mat4(glm::mat3(camera.GetViewMatrix())));
#pragma endregion

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	cleanUp();
	return 0;
}

void cleanUp()
{
	glfwDestroyWindow(window);
	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
}

//keyboard input
void processInput(GLFWwindow *window)
{

#pragma region exit
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE) glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#pragma endregion

#pragma region movement
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera.ProcessKeyboard(FORWARD, deltaTime);
		if (playerBound) {
			if (camera.Position.y < min_altitude) camera.Position.y = min_altitude;
			else if (camera.Position.y > max_altitude) camera.Position.y = max_altitude;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		if (playerBound) {
			if (camera.Position.y < min_altitude) camera.Position.y = min_altitude;
			else if (camera.Position.y > max_altitude) camera.Position.y = max_altitude;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera.ProcessKeyboard(RIGHT, deltaTime);
	}
#pragma endregion

#pragma region print information
	static bool pPressPossible = true;
	if (pPressPossible && 
		glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		pPressPossible = false;
		std::cout << "camera: x: " << camera.Position.x << "    "
			<< "z: " << camera.Position.z << std::endl;
		std::cout << "cactus: x: " << cactusLocAndRot.first[0].x << "    "
			<< "z: " << cactusLocAndRot.first[0].y << std::endl;
		std::cout << "distance: " << getDistance(glm::vec2(camera.Position.x, camera.Position.z), cactusLocAndRot.first[0]) << std::endl << std::endl;
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)  pPressPossible = true;
#pragma endregion

#pragma region switch fullscreen
	static bool window_change_possible = true;
	if (window_change_possible &&
		glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS &&
		glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		window_change_possible = false;
		isFullScreen = !isFullScreen;

		switchFullScreen();
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_RELEASE)  window_change_possible = true;
#pragma endregion

}
//window resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
//mouse movement
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
//mouse scroll
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
//initializing glfw
int initializeGL()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//window creation
	monitorWork();
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader(GLADloadproc(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	if (isFullScreen) glViewport(0, 0, primaryMode->width, primaryMode->height);
	else glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return 0;
}

//switch to fullscreen
void switchFullScreen(void)
{
	if (!primaryMonitor) primaryMonitor = glfwGetPrimaryMonitor();
	if (!primaryMode) primaryMode = glfwGetVideoMode(primaryMonitor);
	if (isFullScreen) glfwSetWindowMonitor(window, primaryMonitor, NULL, NULL, primaryMode->width, primaryMode->height, 0);
	else glfwSetWindowMonitor(window, primaryMonitor, NULL, NULL, SCR_WIDTH, SCR_HEIGHT, 0);
}

//window initialization
void monitorWork()
{
	if (!isFullScreen) window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	else {
		primaryMonitor = glfwGetPrimaryMonitor();
		primaryMode = glfwGetVideoMode(primaryMonitor);
		int count;
		GLFWmonitor** monitors = glfwGetMonitors(&count);

		std::cout << glfwGetMonitorName(primaryMonitor) << " " << &primaryMonitor << std::endl;
		for (int i = 0; i < count; i++) std::cout << glfwGetMonitorName(monitors[i]) << " " + std::to_string(i) << " " << &monitors[i] << std::endl;

		glfwWindowHint(GLFW_RED_BITS, primaryMode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, primaryMode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, primaryMode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, primaryMode->refreshRate);
		window = glfwCreateWindow(primaryMode->width, primaryMode->height, "Level Desert", primaryMonitor, NULL);
	}
}

