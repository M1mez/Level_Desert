#include "GameObject.h"
#include <glad/glad.h>
#include <iostream>
#include "stb_image.h"

GameObject::GameObject(arrayObj<float> verticesObj, arrayObj<unsigned int> indicesObj, glm::vec3 position, Shader *shader) :
	m_vertices(verticesObj), m_indices(indicesObj), m_position(position), m_shader(shader)
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	if (m_indices.size != 0)
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	/*// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);*/
	// texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	return 0;
}

int GameObject::loadTextures()
{
	for (unsigned int index = 0; index < m_textures.size(); index++)
	{
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, m_textures[index]);
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


void GameObject::changePos(const char* shaderVariable, float x, float y, float z, float w) const
{
	int variableLocation = glGetUniformLocation(m_shader->ID, shaderVariable);
	glUseProgram(m_shader->ID);
	glUniform4f(variableLocation, x, y, z, w);
}

void GameObject::changeColor(const char* shaderVariable, float r, float g, float b, float alpha) const
{
	int variableLocation = glGetUniformLocation(m_shader->ID, shaderVariable);
	glUseProgram(m_shader->ID);
	glUniform4f(variableLocation, r, g, b, alpha);
}

int GameObject::addTexture(std::string path, bool isTransparent)
{
	m_shader->use();

	glEnable(GL_DEPTH_TEST);

	unsigned int texId;
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	m_textures.push_back(texId);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, isTransparent ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
		stbi_image_free(data);
		return -1;
	}
	stbi_image_free(data);

	int index = m_textures.size();
	m_shader->setInt("texture" + std::to_string(index + 1), index);
}

GameObject::~GameObject()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	if (m_indices.size != 0)
		glDeleteBuffers(1, &m_EBO);
	delete m_shader;
}

