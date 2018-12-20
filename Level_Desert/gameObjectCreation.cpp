#include <xutility>
#include "forwardDeclaration.h"
#include <glm/detail/type_vec3.hpp>
#include <ctime>
#include "TextureLoading.h"
#include "typeDeclaration.h"
#include "Mesh.h"
#include "model.h"
#include "helperFunctions.h"
#include <iomanip>

class Camera;
// files
extern float planeRadius;
float glassCylinderHeight = 20.0f;

float minObjDistance = 3.5f;

extern Camera camera;

unsigned int glassVAO, glassVBO;
Shader *glassShader;
unsigned int skyboxVAO, skyboxVBO;
Shader *skyBoxShader;
unsigned int skyboxTexture;
Shader  *lenseShader[3];
unsigned int lenseVBO[3];
unsigned int lenseVAO[3];
unsigned int lenseEBO[3];
unsigned int lenseColor[3];
unsigned int lenseTexture;
glm::vec3 lensePositions[3];

extern Mesh *disk;
extern Mesh *glass;
const int floorTriangles = 50;
const int glassTriangles = 36;

#pragma region drawing
// create glass elements at the borders
void drawGlass(glm::mat4 &model, glm::mat4 &projection, glm::mat4 &view, glm::vec3 cameraPos)
{
	glassShader->use();
	glassShader->setMat4("model", model);
	glassShader->setMat4("view", view);
	glassShader->setMat4("projection", projection);
	glassShader->setVec3("cameraPos", cameraPos);
	glBindVertexArray(glassVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
	glDrawArrays(GL_TRIANGLES, 0, glassTriangles * 3);
	glBindVertexArray(0);
}
// draw skybox as last object
void drawSkyBox(glm::mat4 &model, glm::mat4 &projection, glm::mat4 newView)
{
	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	skyBoxShader->use();
	skyBoxShader->setMat4("view", newView);
	skyBoxShader->setMat4("projection", projection);
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}
// draw camera lenses
void drawCameraLenses(glm::mat4 &model, glm::mat4 &projection, glm::mat4 &view, glm::vec3 cameraPos)
{
	std::map<float, int> sorted;
	for (unsigned int i = 0; i < 3; i++) sorted[glm::length(cameraPos - lensePositions[i])] = i;
	
	glEnable(GL_BLEND);
	float lenseDistance = -10.0f;

	for (std::map<float, int>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, lenseTexture);

		model = glm::translate(model, lensePositions[it->second]);

		lenseShader[it->second]->use();
		lenseShader[it->second]->setMat4("projection", projection);
		lenseShader[it->second]->setMat4("view", view);
		lenseShader[it->second]->setMat4("model", model);

		glBindVertexArray(lenseVAO[it->second]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		model = glm::translate(model, -lensePositions[it->second]);
	}
}
#pragma endregion

#pragma region creation
// no model can be closer to another model than minDist
void createLocations(int amount, std::vector <glm::vec2> &locationList, float minDist)
{
	Shader *shader = getShader(VERTEX_PERM_MODEL, FRAGMENT_PERM_MODEL);
	for (int i = 0; i < amount; i++)
	{
		glm::vec2 newLoc;
		if (getValidVec2InBounds(locationList, &newLoc, minDist) < 0) return;
		locationList.push_back(newLoc);
	}
}
// create plane circle as floor
Mesh *createPlaneDisk(void)
{
	std::vector<Vertex> vv;

	const float triangleFraction = static_cast<float>(360) / floorTriangles;
	float continuousFloat = 0.0f;

	for (int i = 0; i < 360;)
	{
		continuousFloat += triangleFraction;
		i = static_cast<int>(continuousFloat);

		const float rad1 = glm::radians(continuousFloat);
		const float rad2 = glm::radians(continuousFloat + triangleFraction);

		Vertex v1;
		v1.Position = glm::vec3(
			glm::cos(rad1) * planeRadius,
			0.0f,
			glm::sin(rad1) * planeRadius);
		v1.TexCoords = glm::vec2(
			(1 + v1.Position.x) * 4 / planeRadius,
			(1 + v1.Position.z) * 4 / planeRadius
		);
		vv.push_back(v1);

		Vertex v2;
		v2.Position = glm::vec3(
			glm::cos(rad2) * planeRadius,
			0.0f,
			glm::sin(rad2) * planeRadius);
		v2.TexCoords = glm::vec2(
			(1 + v2.Position.x) * 4 / planeRadius,
			(1 + v2.Position.z) * 4 / planeRadius
		);
		vv.push_back(v2);

		Vertex v3;
		v3.Position = glm::vec3(0.0f, 0.0f, 0.0f);
		v3.TexCoords = glm::vec2(0.5f, 0.5f);
		vv.push_back(v3);
	}
	std::vector<unsigned int> indices;
	unsigned int fi = 0;
	for (unsigned int i = 0; i < vv.size(); i++)
	{
		for (unsigned int ri = 0; ri < 3; ri++)
			indices.push_back(ri + i);
	}

	//Shader *shader = getShader(VERTEX_CAMERA, FRAGMENT_CAMERA);
	Shader *shader = getShader(VERTEX_PERM_MODEL, FRAGMENT_PERM_MODEL);

	Texture t;
	t.path = "models/desertfloor/desertfloorsmall.png";
	t.id = storeTexture(t.path, false, shader);
	t.type = "texture_diffuse";
	std::vector<Texture> tv;
	tv.push_back(t);

	Mesh *m = new Mesh(vv, indices, tv);
	m->setShader(shader);
	return m;
}
// create 3 windows to showcase transparency
void createCameraLenses(void)
{

	for (int i = 0; i < 3; i++)
	{
		lenseShader[i] = getShader(VERTEX_BLENDING, FRAGMENT_BLENDING);

		float rgb[3] = { 0.0f };
		rgb[i] = 1.0f;
		float size = 6.0f;
		float posOffset = 8.0f * i;

		lensePositions[i] = glm::vec3(0.0f, 0.0f, size + posOffset);

		float vertices[] = {
			 // positions						// colors						// texture coords
			 size,  2 * size,	0.0f,			rgb[0], rgb[1], rgb[2],			1.0f, 1.0f,
			 size,	0.0f,		0.0f,			rgb[0], rgb[1], rgb[2],			1.0f, 0.0f,
			-size,	0.0f,		0.0f,			rgb[0], rgb[1], rgb[2],			0.0f, 0.0f,
			-size,  2 * size,	0.0f,			rgb[0], rgb[1], rgb[2],			0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		lenseTexture = storeTexture("models/window/cookie.png", false, lenseShader[i]);


		lenseVBO[i] = VBO;
		lenseVAO[i] = VAO;
		lenseEBO[i] = EBO;
	}
}
// create glass walls at border
Mesh *createGlass(void)
{
	float vertices[glassTriangles * 18];

	const float triangleFraction = static_cast<float>(360) / glassTriangles;
	float continuousFloat = 0.0f;
	bool firstHalf = false;
	float rad = glm::radians(triangleFraction);
	int count = 0;
	for (int i = 0; i < 360;)
	{
		continuousFloat += triangleFraction;
		i = static_cast<int>(continuousFloat);

		float xPos1 = glm::cos(rad) * planeRadius;
		float zPos1 = glm::sin(rad) * planeRadius;
		rad = glm::radians(continuousFloat + triangleFraction);
		float xPos2 = glm::cos(rad) * planeRadius;
		float zPos2 = glm::sin(rad) * planeRadius;

		addVertexWithNormals(xPos1, zPos1, !firstHalf ? glassCylinderHeight : 0.0f, vertices, count);
		addVertexWithNormals(xPos1, zPos1, firstHalf ? glassCylinderHeight : 0.0f, vertices, count);
		addVertexWithNormals(xPos2, zPos2, !firstHalf ? glassCylinderHeight : 0.0f, vertices, count);
	}

	glassShader = getShader(VERTEX_WALL_REFRACTION, FRAGMENT_WALL_REFRACTION);

	glGenVertexArrays(1, &glassVAO);
	glGenBuffers(1, &glassVBO);
	glBindVertexArray(glassVAO);
	glBindBuffer(GL_ARRAY_BUFFER, glassVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	return nullptr;
}
// create 3 cactus-LOD models in parameter vector
void createCactus(std::vector<Model*> &vector)
{
	Shader *shader;
	Model *newM;;

	shader = getShader(VERTEX_PERM_MODEL, FRAGMENT_PERM_MODEL);
	newM = new Model(getModelLoc(MODEL_CACTUS_1_LOD0), shader);
	newM->setScale(10.0f);
	//newM->setRotation(glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(-90.0f, 0.0f, 0.0f));
	newM->setRotation(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	newM->prioAxis = 1;
	vector.push_back(newM);

	shader = getShader(VERTEX_PERM_MODEL, FRAGMENT_PERM_MODEL);
	newM = new Model(getModelLoc(MODEL_CACTUS_1_LOD1), shader);
	newM->setScale(10.0f);
	newM->setRotation(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	newM->prioAxis = 1;
	vector.push_back(newM);

	shader = getShader(VERTEX_PERM_MODEL, FRAGMENT_PERM_MODEL);
	newM = new Model(getModelLoc(MODEL_CACTUS_1_LOD2), shader);
	newM->setScale(10.0f);
	newM->setRotation(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	newM->prioAxis = 1;
	vector.push_back(newM);
}
// to test model-loading
Model *createNanoSuit(void)
{
	Shader *shader = getShader(VERTEX_PERM_MODEL, FRAGMENT_PERM_MODEL);
	return new Model(getModelLoc(MODEL_NANOSUIT), shader);
}
// create skybox with textured faces
void createSkyBox(void)
{
	float skyboxVertices[] = {
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
	std::vector<std::string> faces{
		"skyboxes/tutskybox/right.jpg",
		"skyboxes/tutskybox/left.jpg",
		"skyboxes/tutskybox/top.jpg",
		"skyboxes/tutskybox/bottom.jpg",
		"skyboxes/tutskybox/front.jpg",
		"skyboxes/tutskybox/back.jpg"
	};

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	skyboxTexture = loadCubemap(faces);
	skyBoxShader = getShader(VERTEX_SKYBOX, FRAGMENT_SKYBOX);

	skyBoxShader->use();
	skyBoxShader->setInt("skybox", 0);
}
// skybox, disk and glasswalls don't need further information, so creation is bundled
void createScenery(void)
{
	createSkyBox();
	disk = createPlaneDisk();
	glass = createGlass();
	createCameraLenses();
}
#pragma endregion