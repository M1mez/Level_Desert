#include <xutility>
#include "forwardDeclaration.h"
#include <glm/detail/type_vec3.hpp>
#include <ctime>
#include "TextureLoading.h"
#include "typeDeclaration.h"


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

	obj->addTexture(storeTexture("textures/container.jpg", false, shader, 0));
	obj->addTexture(storeTexture("textures/awesomeface.png", true, shader, 1));

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

	obj->addTexture(storeTexture("textures/desertfloor1.jpg", false, shader, 0));

	return obj;
}

GameObject *createPlaneDisk(void)
{
	std::vector<float> vv;
	float radius = 5.0f;
	int triangles = 50;

	const float triangleFraction = static_cast<float>(360) / triangles;
	float continuousFloat = 0.0f;

	for (int i = 0; i < 360; i++)
	{
		continuousFloat += triangleFraction;
		i = static_cast<int>(continuousFloat);

		const int i2 = i + static_cast<int>(triangleFraction);
		const float f2 = continuousFloat + triangleFraction;

		vv.push_back(glm::cos(glm::radians(continuousFloat)) * radius);
		vv.push_back(0.0f);
		vv.push_back(glm::sin(glm::radians(continuousFloat)) * radius);
		
		/*vv.push_back(i2 % 2 ? 0.0f : 1.0f);
		vv.push_back(i2 % 2 ? 0.0f : 1.0f);*/

		vv.push_back(glm::cos(glm::radians(f2)) * radius);
		vv.push_back(0.0f);
		vv.push_back(glm::sin(glm::radians(f2)) * radius);
		
		/*vv.push_back(i2 % 2 ? 1.0f : 0.0f);
		vv.push_back(i2 % 2 ? 0.0f : 1.0f);*/

		vv.push_back(0.0f);
		vv.push_back(0.0f);
		vv.push_back(0.0f);
	
		/*vv.push_back(i2 % 2 ? 1.0f : 0.0f);
		vv.push_back(i2 % 2 ? 1.0f : 0.0f);*/
	}

	float textureCoords[] = {
		    0.0f,  0.0f, 
			1.0f,  0.0f, 
			1.0f,  1.0f, 
			1.0f,  1.0f, 
		    0.0f,  1.0f, 
		    0.0f,  0.0f,
			
			0.0f,  0.0f,
			1.0f,  0.0f,
			1.0f,  1.0f,
			1.0f,  1.0f,
			0.0f,  1.0f,
			0.0f,  0.0f
	};

	const struct arrayObj<float> verticesObj = { vv.size() * sizeof(float), (&vv[0]) };
	const struct arrayObj<float> textureObj = { sizeof textureCoords, textureCoords };
	Shader *shader = getShader(VERTEX_CAMERA, FRAGMENT_CAMERA);

	GameObject *obj = new GameObject(shader, verticesObj);

	obj->addTexture(storeTexture("textures/desertfloor1.jpg", false, shader));

	//obj->setTextureCoords(textureObj);

	return obj;
}

GameObject *createSkyBox(void)
{
	return nullptr;
}