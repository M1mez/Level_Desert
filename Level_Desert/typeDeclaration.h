#pragma once

#include <glm/glm.hpp>
#include <string>

enum vertexShaderType {
	VERTEX_NONE, 
	VERTEX_SIMPLE,
	VERTEX_SIMPLE_TEXTURE,
	VERTEX_CAMERA
};
enum fragmentShaderType { 
	FRAGMENT_NONE, 
	FRAGMENT_SIMPLE_1, 
	FRAGMENT_SIMPLE_TEXTURE,
	FRAGMENT_CAMERA
};

template <typename T>
struct arrayObj {
	size_t size;
	T *data;
};

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};