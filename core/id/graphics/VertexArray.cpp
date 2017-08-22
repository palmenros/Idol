#include "VertexArray.h"
#include "id/OpenGL.h"

namespace Idol
{
VertexArray::VertexArray() : ibo(nullptr)
{
	glGenVertexArrays(1, &vao);
}

VertexArray::~VertexArray()
{
	for (Buffer* buffer : buffers)
	{
		delete buffer;
	}

	delete ibo;

	glDeleteVertexArrays(1, &vao);
}

void VertexArray::bind() const
{
	glBindVertexArray(vao);
}

void VertexArray::push(Buffer* buffer)
{
	buffers.push_back(buffer);
}

void VertexArray::setLayout()
{
	bind();
	for (Buffer* buffer : buffers)
	{
		buffer->setLayout();
	}
}

void VertexArray::setIndexBuffer(IndexBuffer* ibo)
{
	this->ibo = ibo;
}

void VertexArray::draw(size_t count) const
{
	bind();

	if (ibo)
	{
		glDrawElements(GL_TRIANGLES, ibo->getSize(), GL_UNSIGNED_INT, nullptr);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, count);
	}
}
}
