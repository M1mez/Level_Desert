#include "GameObject.h"
#include <glad/glad.h>
#include <iostream>
#include "stb_image.h"
#include "TextureLoading.h"

GameObject::GameObject(Shader *shader, arrayObj<float> verticesObj, arrayObj<unsigned int> indicesObj) 
	: m_shader(shader)
{
	setVertexCoords(verticesObj);
	setIndices(indicesObj);
	m_indicesSet = m_texturesSet = m_colorsSet = false;

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	initializeGlOBjects();
}

GameObject::GameObject(Shader* shader, arrayObj<float> verticesObj)
	: m_shader(shader)
{
	setVertexCoords(verticesObj);
	m_indicesSet = m_texturesSet = m_colorsSet = false;

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	initializeGlOBjects();
}

GameObject::GameObject(Shader* shader)
	: m_shader(shader)
{
	m_indicesSet = m_texturesSet = m_colorsSet = false;

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	initializeGlOBjects();
}

int GameObject::initializeGlOBjects()
{
	// ..:: Initialization code (done once (unless your object frequently changes)) :: ..
	// 1. bind Vertex Array Object
	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size, m_vertices.data, GL_STATIC_DRAW);

	if (m_indices.size != 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size, m_indices.data, GL_STATIC_DRAW);
	}

	/*// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, m_VAO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size, m_vertices.data, GL_STATIC_DRAW);*/

	// 3. then set our vertex attributes pointers
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	/*// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);*/
	// texture attribute
	/*glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);*/

	return 0;
}

int GameObject::loadTextures()
{
	for (unsigned int index = 0; index < m_textureIDs.size(); index++)
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, m_textureIDs[index]);
	}
	return 0;
}

void GameObject::Draw()
{
	if (false) initializeGlOBjects();

	//texture
	loadTextures();
	m_shader->use();


	glBindVertexArray(m_VAO);
	if (m_indices.size == 0)
		glDrawArrays(GL_TRIANGLES, 0, m_vertices.size/sizeof(float)/5*3);
	else
		glDrawElements(GL_TRIANGLES, m_indices.size / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	//unbind
	glBindVertexArray(0);
}

void GameObject::setMat4(const std::string &name, const glm::mat4 &mat) const
{
	m_shader->setMat4(name, mat);
}

void GameObject::setVertexCoords(arrayObj<float> v)
{
	m_vertices = v;
}

void GameObject::setIndices(arrayObj<unsigned int> i)
{
	m_indices = i;
	m_indicesSet = true;
}

void GameObject::setColorCoords(arrayObj<float> c)
{
	m_colors = c;
	m_colorsSet = true;
}

void GameObject::setTextureCoords(arrayObj<float> t)
{
	m_textures = t;
	m_texturesSet = true;

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_textures.size, m_textures.data, GL_STATIC_DRAW);
	
	//texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
}

void GameObject::addTexture(unsigned texId)
{
	m_textureIDs.push_back(texId);
}

GameObject::~GameObject()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	if (m_indicesSet) glDeleteBuffers(1, &m_EBO);
	delete m_shader;
}



/*
void GameObject::changePos(const char* shaderVariable, float x, float y, float z, float w) const
{
	int variableLocation = glGetUniformLocation(m_shader->ID, shaderVariable);
	glUseProgram(m_shader->ID);
	glUniform4f(variableLocation, x, y, z, w);
}*/