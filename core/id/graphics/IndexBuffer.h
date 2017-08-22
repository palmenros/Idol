#pragma once

#include "Buffer.h"

namespace Idol
{

class IndexBuffer
{
private:
	uint ebo;
	size_t triangleCount;
	BufferUsage usage;
	size_t size;
public:

	IndexBuffer(BufferUsage usage = BufferUsage::Static);
	~IndexBuffer();

	void setData(uint* data, size_t size);
	size_t getSize() const;

	void bind() const;

};

}