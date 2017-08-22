#pragma once

#include "BufferLayout.h"

namespace Idol
{

enum class BufferUsage
{
	Static,
	Dynamic
};

class Buffer
{
private:

	uint buffer;
	BufferLayout layout;
	BufferUsage usage;

public:

	static uint bufferUsageToOpenGL(BufferUsage usage);

	Buffer(const BufferLayout& layout, BufferUsage usage = BufferUsage::Static);
	~Buffer();

	void bind() const;

	void setData(const void* data, size_t count);
	void setLayout();
};
}
