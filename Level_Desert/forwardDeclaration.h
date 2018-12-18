#pragma once
#include "Mesh.h"
#include "model.h"
#include "GameObject.h"

// creation
void createLocations(int amount, std::vector <glm::vec2> &locationList, float minDist);
Mesh *createPlaneDisk(void);
Mesh *createGlass(void);
void createSkyBox(void);
Model *createStoneTree(void);
void createScenery(void);
void createCactus(std::vector<Model*> &vector);
void createCameraLenses(void);

// draw
void drawSkyBox(glm::mat4 &model, glm::mat4 &projection, glm::mat4 newView);
void drawGlass(glm::mat4 &model, glm::mat4 &projection, glm::mat4 &view, glm::vec3 cameraPos);
void drawCameraLenses(glm::mat4 &model, glm::mat4 &projection, glm::mat4 &view, glm::vec3 cameraPos);

// Maps
std::string getModelLoc(modelLocationType model);
Shader *getShader(vertexShaderType v, fragmentShaderType f);

// initialize dictionary of resources
void initializeMaps(void);

// not needed
Model *createNanoSuit(void);

