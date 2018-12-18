#include <map>
#include <glad/glad.h>
#include <iostream>
#include "forwardDeclaration.h"

// ReSharper disable CppJoinDeclarationAndAssignment


std::string shaderLocation = "shaderFiles/";
std::string modelLocation = "models/";

#pragma region shaders
std::map<vertexShaderType, std::string> vertexShaders;			// position data and model
std::map<fragmentShaderType, std::string> fragmentShaders;		// colour output of the pixels

Shader *getShader(vertexShaderType v, fragmentShaderType f){return new Shader(vertexShaders[v], fragmentShaders[f]);}
void initializeShaderMap()
{
#pragma region vertex
	vertexShaders[VERTEX_SIMPLE_TEXTURE] = shaderLocation + "VERTEX_SIMPLE_TEXTURE.vs";
	vertexShaders[VERTEX_CAMERA] = shaderLocation + "VERTEX_CAMERA.vs";
	vertexShaders[VERTEX_SKYBOX] = shaderLocation + "VERTEX_SKYBOX.vs";
	vertexShaders[VERTEX_SKYBOX_CUBEMAP] = shaderLocation + "VERTEX_SKYBOX_CUBEMAP.vs";
	vertexShaders[VERTEX_PERM_MODEL] = shaderLocation + "VERTEX_PERM_MODEL.vs";
	vertexShaders[VERTEX_WALL_REFRACTION] = shaderLocation + "VERTEX_WALL_REFRACTION.vs";
	vertexShaders[VERTEX_BLENDING] = shaderLocation + "VERTEX_BLENDING.vs";
#pragma endregion
#pragma region fragment
	fragmentShaders[FRAGMENT_SKYBOX] = shaderLocation + "FRAGMENT_SKYBOX.fs";
	fragmentShaders[FRAGMENT_SKYBOX_CUBEMAP] = shaderLocation + "FRAGMENT_SKYBOX_CUBEMAP.fs";
	fragmentShaders[FRAGMENT_PERM_MODEL] = shaderLocation + "FRAGMENT_PERM_MODEL.fs";
	fragmentShaders[FRAGMENT_WALL_REFRACTION] = shaderLocation + "FRAGMENT_WALL_REFRACTION.fs";
	fragmentShaders[FRAGMENT_BLENDING] = shaderLocation + "FRAGMENT_BLENDING.fs";
#pragma endregion
}
#pragma endregion

#pragma region models
std::map<modelLocationType, std::string> modelLocations;			// position data and model

std::string getModelLoc(modelLocationType model){return modelLocations[model];}
void initializeModelMap()
{
	modelLocations[MODEL_NANOSUIT] = modelLocation + "nanosuit/nanosuit.obj";
	modelLocations[MODEL_CACTUS_1_LOD0] = modelLocation + "cactus1/cactus1lod0.obj";
	modelLocations[MODEL_CACTUS_1_LOD1] = modelLocation + "cactus1/cactus1lod1.obj";
	modelLocations[MODEL_CACTUS_1_LOD2] = modelLocation + "cactus1/cactus1lod2.obj";
}
#pragma endregion

void initializeMaps(void)
{
	initializeShaderMap();
	initializeModelMap();
}

// ReSharper restore CppJoinDeclarationAndAssignment