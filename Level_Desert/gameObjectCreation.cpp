#include <xutility>
#include "forwardDeclaration.h"
#include <glm/detail/type_vec3.hpp>


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
	GameObject *obj = new GameObject(verticesObj, indicesObj, position, shader);

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
	GameObject *obj = new GameObject(verticesObj, indicesObj, position, shader);

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

	GameObject *obj = new GameObject(verticesObj, indicesObj, position, shader);

	obj->addTexture("textures/container.jpg", false);
	obj->addTexture("textures/awesomeface.png", true);

	return obj;
}

GameObject* createPlane(void)
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

	GameObject *obj = new GameObject(verticesObj, indicesObj, position, shader);

	obj->addTexture("textures/desertfloor1.jpg", false);

	return obj;
}