#pragma once

#include <vector>
#include "id/Types.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "id/Common.h"

namespace Idol
{
struct BufferElement
{
	int index;
	size_t count;
	GLenum type;
	GLboolean normalized;


	BufferElement(int index, size_t count, GLenum type, GLboolean normalized = GL_FALSE)
		: index(index),
		  count(count),
		  type(type),
		  normalized(normalized)
	{
	}

	static size_t getOpenGLTypeSize(GLenum type)
	{
		switch (type)
		{
		case GL_BYTE: return sizeof(GLbyte);
		case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
		case GL_SHORT: return sizeof(GLshort);
		case GL_UNSIGNED_SHORT: return sizeof(GLushort);
		case GL_INT: return sizeof(GLint);
		case GL_UNSIGNED_INT: return sizeof(GLuint);
		case GL_FIXED: return sizeof(GLfixed);
		case GL_HALF_FLOAT: return sizeof(GLhalf);
		case GL_FLOAT: return sizeof(GLfloat);
		case GL_DOUBLE: return sizeof(GLdouble);
		default: 
			ERROR("OpenGL type not recognized when getting size: " + std::to_string(type));
			return 0;
		}
	}

	size_t getSize() const
	{
		return count * getOpenGLTypeSize(type);
	}
};

class BufferLayout
{
public:

	std::vector<BufferElement> elements;

	void pushElement(const BufferElement& element);
	void setLayout();
};
}
