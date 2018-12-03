#include <map>
#include <glad/glad.h>
#include <iostream>
#include "forwardDeclaration.h"

// ReSharper disable CppJoinDeclarationAndAssignment


// position data and model
std::map<vertexShaderType, std::string> vertexShaders;
// colour output of the pixels
std::map<fragmentShaderType, std::string> fragmentShaders;

extern std::string shaderLocation;

Shader *getShader(vertexShaderType v, fragmentShaderType f)
{
	return new Shader(vertexShaders[v], fragmentShaders[f]);
}

void initializeShaderMap()
{
#pragma region tutorial vertex
	vertexShaders[VERTEX_SIMPLE] = shaderLocation + "VERTEX_SIMPLE.vs";
	vertexShaders[VERTEX_SIMPLE_TEXTURE] = shaderLocation + "VERTEX_SIMPLE_TEXTURE.vs";
	vertexShaders[VERTEX_CAMERA] = shaderLocation + "VERTEX_CAMERA.vs";
#pragma endregion

#pragma region tutorial fragment
	fragmentShaders[FRAGMENT_SIMPLE_1] = shaderLocation + "FRAGMENT_SIMPLE_1.fs";
	fragmentShaders[FRAGMENT_SIMPLE_TEXTURE] = shaderLocation + "FRAGMENT_SIMPLE_TEXTURE.fs";
	fragmentShaders[FRAGMENT_CAMERA] = shaderLocation + "FRAGMENT_CAMERA.fs";
#pragma endregion

#pragma region light

#pragma endregion
}

/*
int bindShader(GLenum shaderType, unsigned int &shaderID, const char *shaderSource)
{
	int  success;
	char infoLog[512];
	const char* shaderTypeString;

	switch (shaderType)
	{
	case GL_VERTEX_SHADER:
	{
		shaderTypeString = "Vertex Shader";
		break;
	}
	case GL_FRAGMENT_SHADER:
	{
		shaderTypeString = "Fragment Shader";
		break;
	}
	default:
	{
		std::cout << "ERROR::SHADER::UNKNOWN_TYPE: " << shaderType << std::endl;
		return -1;
	}
	}

	shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderSource, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}
	return 0;
}
 int createProgram(unsigned int &programID, vertexShaderType vertex, fragmentShaderType fragment)
{
	int  success;
	char infoLog[512];
	unsigned int vertexID, fragmentID;
	
	programID = glCreateProgram();

	if (vertex != VERTEX_NONE)
	{
		bindShader(GL_VERTEX_SHADER, vertexID, vertexShaders[vertex]);
		glAttachShader(programID, vertexID);
	}
	if (fragment != FRAGMENT_NONE) 
	{
		bindShader(GL_FRAGMENT_SHADER, fragmentID, fragmentShaders[fragment]);
		glAttachShader(programID, fragmentID);
	}


	glLinkProgram(programID);

	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
		return -1;
	}
	if (vertex != VERTEX_NONE) glDeleteShader(vertexID);
	if (fragment != FRAGMENT_NONE) glDeleteShader(vertexID);
	
	return 0;
}*/


// ReSharper restore CppJoinDeclarationAndAssignment