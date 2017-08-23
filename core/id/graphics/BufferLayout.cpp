#include "BufferLayout.h"
#include "id/OpenGL.h"

namespace Idol
{
void BufferLayout::pushElement(const BufferElement& element)
{
	elements.push_back(element);
}

void BufferLayout::setLayout()
{
	size_t offset = 0;
	size_t stride = 0;

	//Calculate stride
	for (const BufferElement& e : elements)
	{
		stride += e.getSize();
	}

	for (const BufferElement& e : elements)
	{
		if (e.index >= 0)
		{
			glVertexAttribPointer(e.index, e.count, e.type, e.normalized, stride, (void*)offset);
			glEnableVertexAttribArray(e.index);
		}

		//If index is negative, ignore it because is just padding
		offset += e.getSize();
	}
}
}
