#pragma once
#include <vector>
#include "Buffer.h"
#include "IndexBuffer.h"

namespace Idol
{

class VertexArray
{
private:

	std::vector<Buffer*> buffers;
	uint vao;
	IndexBuffer* ibo;

public:

	VertexArray();
	~VertexArray();

	void bind() const;

	void push(Buffer* buffer);
	void setLayout();

	void setIndexBuffer(IndexBuffer* ibo);

	void draw(size_t count = 0) const;

};


}