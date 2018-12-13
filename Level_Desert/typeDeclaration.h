#pragma once

#include <glm/glm.hpp>
#include <string>

enum vertexShaderType {
	VERTEX_NONE,
	VERTEX_CAMERA,
	VERTEX_PERM_MODEL,
	VERTEX_SIMPLE_TEXTURE,
	VERTEX_SKYBOX, 
	VERTEX_SKYBOX_CUBEMAP,
	VERTEX_WALL_REFRACTION
};
enum fragmentShaderType { 
	FRAGMENT_NONE, 
	FRAGMENT_CAMERA,
	FRAGMENT_PERM_MODEL,
	FRAGMENT_SKYBOX,
	FRAGMENT_SKYBOX_CUBEMAP,
	FRAGMENT_WALL_REFRACTION
};
enum modelLocationType {
	MODEL_NANOSUIT,
	MODEL_CACTUS_1_LOD0,
	MODEL_CACTUS_1_LOD1,
	MODEL_CACTUS_1_LOD2,
};

template <typename T>
struct arrayObj {
	size_t size;
	T *data;
};

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};