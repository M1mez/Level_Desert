#pragma once
#include "GameObject.h"

// creation
extern GameObject* createSimpleTriangleFixedMidScreen(void);
extern GameObject* createSimpleRectangleFixedMidScreen(void);
extern GameObject* createPlane(void);
GameObject *createCubeInSpace(void);
Shader *getShader(vertexShaderType v, fragmentShaderType f);