#include <xutility>
#include "forwardDeclaration.h"
#include <glm/detail/type_vec3.hpp>
#include <ctime>


GameObject* createSimpleTriangleFixedMidScreen(void)
{
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0   // first triangle
	};

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

	const struct arrayObj<float> verticesObj = { sizeof vertices, vertices };
	const struct arrayObj<unsigned int> indicesObj = { 0, indices };
	Shader *shader = getShader(VERTEX_SIMPLE, FRAGMENT_SIMPLE_1);
	GameObject *obj = new GameObject(shader, verticesObj, indicesObj);

	return obj;
}

GameObject* createSimpleRectangleFixedMidScreen(void)
{
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

	const struct arrayObj<float> verticesObj = { sizeof vertices, vertices };
	const struct arrayObj<unsigned int> indicesObj = { sizeof indices, indices };
	Shader *shader = getShader(VERTEX_SIMPLE_TEXTURE, FRAGMENT_SIMPLE_TEXTURE);
	GameObject *obj = new GameObject(shader, verticesObj, indicesObj);

	return obj;
}

GameObject *createCubeInSpace(void)
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
   // ------------------------------------------------------------------
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	unsigned int indices[] = { 0 };

	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

	const struct arrayObj<float> verticesObj = { sizeof vertices, vertices };
	const struct arrayObj<unsigned int> indicesObj = { 0, indices };
	Shader *shader = getShader(VERTEX_CAMERA, FRAGMENT_CAMERA);

	GameObject *obj = new GameObject(shader, verticesObj, indicesObj);

	obj->addTexture("textures/container.jpg", false);
	obj->addTexture("textures/awesomeface.png", true);

	return obj;
}

GameObject* createPlaneSquare(void)
{
	float vertices[] = {
		   -1.0f,  0.0f, -1.0f,  0.0f, 0.0f,
			1.0f,  0.0f, -1.0f,  1.0f, 0.0f,
			1.0f,  0.0f, 1.0f,  1.0f, 1.0f,
			1.0f,  0.0f, 1.0f,  1.0f, 1.0f,
		   -1.0f,  0.0f, 1.0f,  0.0f, 1.0f,
		   -1.0f,  0.0f, -1.0f,  0.0f, 0.0f
	};

	for (unsigned int i = 0; i < sizeof(vertices) / sizeof(float); i++)
	{
		vertices[i] *= 5;
	}

	unsigned int indices[] = { 0 };
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

	const struct arrayObj<float> verticesObj = { sizeof vertices, vertices };
	const struct arrayObj<unsigned int> indicesObj = { 0, indices };
	Shader *shader = getShader(VERTEX_CAMERA, FRAGMENT_CAMERA);

	GameObject *obj = new GameObject(shader, verticesObj, indicesObj);

	obj->addTexture("textures/desertfloor1.jpg", false);

	return obj;
}

GameObject *createPlaneDisk(void)
{
	std::vector<float> vv;
	float radius = 5.0f;

	srand(time(0));
	int randomval = rand() % 2;

	for (int i = 0; i < 360; i++)
	{
		const float f(i);
		const int i2 = i + 1;
		const float f2(i2);

		vv.push_back(glm::cos(glm::radians(f)) * radius);
		vv.push_back(0.0f);
		vv.push_back(glm::sin(glm::radians(f)) * radius);
		vv.push_back(i2 % 2 ? 0.0f : 1.0f);
		vv.push_back(i2 % 2 ? 0.0f : 1.0f);

		vv.push_back(glm::cos(glm::radians(f2)) * radius);
		vv.push_back(0.0f);
		vv.push_back(glm::sin(glm::radians(f2)) * radius);
		vv.push_back(i2 % 2 ? 1.0f : 0.0f);
		vv.push_back(i2 % 2 ? 0.0f : 1.0f);

		vv.push_back(0.0f);
		vv.push_back(0.0f);
		vv.push_back(0.0f);
		vv.push_back(i2 % 2 ? 1.0f : 0.0f);
		vv.push_back(i2 % 2 ? 1.0f : 0.0f);
	}

	unsigned int indices[] = { 0 };
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

	const struct arrayObj<float> verticesObj = { vv.size() * sizeof(float), (&vv[0]) };
	const struct arrayObj<unsigned int> indicesObj = { 0, indices };
	Shader *shader = getShader(VERTEX_CAMERA, FRAGMENT_CAMERA);

	GameObject *obj = new GameObject(shader, verticesObj, indicesObj);

	obj->addTexture("textures/desertfloor1.jpg", false);

	return obj;
}

GameObject *createSkyBox(void)
{
	return nullptr;
}