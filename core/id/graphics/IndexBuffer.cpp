#include "IndexBuffer.h"
#include "id/OpenGL.h"


namespace Idol
{
IndexBuffer::IndexBuffer(BufferUsage usage) : usage(usage)
{
	glGenBuffers(1, &ebo);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &ebo);
}

void IndexBuffer::setData(uint* data, size_t size)
{
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, Buffer::bufferUsageToOpenGL(usage));
	this->size = size;
}

size_t IndexBuffer::getSize() const
{
	return size;
}

void IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}


}
