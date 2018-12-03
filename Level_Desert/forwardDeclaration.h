#pragma once
#include "GameObject.h"

// creation
GameObject* createSimpleTriangleFixedMidScreen(void);
GameObject* createSimpleRectangleFixedMidScreen(void);
GameObject* createPlaneSquare(void);
GameObject *createPlaneDisk(void);
GameObject *createCubeInSpace(void);
GameObject *createSkyBox(void);
Shader *getShader(vertexShaderType v, fragmentShaderType f);