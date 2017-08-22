#include "Buffer.h"
#include "id/OpenGL.h"

namespace Idol
{
uint Buffer::bufferUsageToOpenGL(BufferUsage usage)
{
	switch(usage)
	{
	case BufferUsage::Static: return GL_STATIC_DRAW;
	case BufferUsage::Dynamic: return GL_DYNAMIC_DRAW;
	default: return 0;
	}
}

Buffer::Buffer(const BufferLayout& layout, BufferUsage usage)
	: layout(layout), usage(usage)
{
	glGenBuffers(1, &buffer);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &buffer);
}

void Buffer::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

void Buffer::setData(const void* data, size_t count)
{
	bind();
	glBufferData(GL_ARRAY_BUFFER, count, data, bufferUsageToOpenGL(usage));
}

void Buffer::setLayout()
{
	bind();
	layout.setLayout();
}
}
