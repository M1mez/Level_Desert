#pragma once
#include "enums.h"
#include "Shader.h"
#include <vector>
#include <glm/mat4x4.hpp>

class GameObject
{
public:
	explicit GameObject(arrayObj<float> verticesObj, arrayObj<unsigned int> indicesObj, glm::vec3 position, Shader *shader);

	glm::vec3 m_position;

	void Draw();
	void setMat4(const std::string &name, const glm::mat4 &mat) const;
	void changePos(const char* shaderVariable, float x, float y, float z, float w = 1.0f) const;
	void changeColor(const char* shaderVariable, float r, float g, float b, float alpha = 1.0f) const;
	int addTexture(std::string path, bool isTransparent);
	~GameObject();

private:
	int initializeGlOBjects();
	int loadTextures();

	arrayObj<float> m_vertices;
	arrayObj<unsigned int> m_indices;
	unsigned int m_VBO;
	unsigned int m_EBO;
	unsigned int m_VAO;
	std::vector<unsigned int> m_textures;
	Shader *m_shader;
};

