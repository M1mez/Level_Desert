#pragma once

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

struct imageObj
{
	
};