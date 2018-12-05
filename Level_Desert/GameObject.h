#pragma once
#include "Shader.h"
#include <vector>
#include <glm/mat4x4.hpp>
#include "typeDeclaration.h"

class GameObject
{
public:
	explicit GameObject(Shader *shader, arrayObj<float> verticesObj, arrayObj<unsigned int> indicesObj);
	explicit GameObject(Shader *shader, arrayObj<float> verticesObj);
	explicit GameObject(Shader *shader);

	glm::vec3 m_position;

	void Draw();
	void setMat4(const std::string &name, const glm::mat4 &mat) const;

	void setVertexCoords(arrayObj<float> v);
	void setIndices(arrayObj<unsigned int> t);
	void setColorCoords(arrayObj<float> c);
	void setTextureCoords(arrayObj<float> t);

	void addTexture(unsigned int texId);

	~GameObject();

private:
	int initializeGlOBjects();
	int loadTextures();

	arrayObj<float> m_vertices;
	arrayObj<unsigned int> m_indices;
	bool m_indicesSet;
	arrayObj<float> m_colors;
	bool m_colorsSet;
	arrayObj<float> m_textures;
	bool m_texturesSet;

	unsigned int m_VBO;
	unsigned int m_EBO;
	unsigned int m_VAO;
	std::vector<unsigned int> m_textureIDs;
	Shader *m_shader;
};

