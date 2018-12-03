#pragma once
#include "enums.h"
#include "Shader.h"
#include <vector>
#include <glm/mat4x4.hpp>

class GameObject
{
public:
	explicit GameObject(Shader *shader, arrayObj<float> verticesObj, arrayObj<unsigned int> indicesObj);
	explicit GameObject(Shader *shader, arrayObj<float> verticesObj);
	explicit GameObject(Shader *shader);

	glm::vec3 m_position;

	void Draw();
	void setMat4(const std::string &name, const glm::mat4 &mat) const;

	void setVertices(arrayObj<float> v);
	void setIndices(arrayObj<unsigned int> t);
	void setColorPerV(arrayObj<float> c);
	void setTexturePerV(arrayObj<float> t);

	int addTexture(std::string path, bool isTransparent);
	unsigned int loadCubemap(std::vector<std::string> faces);

	~GameObject();

private:
	int initializeGlOBjects();
	int loadTextures();

	arrayObj<float> m_vertices;
	arrayObj<unsigned int> m_indices; 
	bool m_indicesSet;

	unsigned int m_VBO;
	unsigned int m_EBO;
	unsigned int m_VAO;
	std::vector<unsigned int> m_textures;
	Shader *m_shader;
};

