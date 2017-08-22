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
		glVertexAttribPointer(e.index, e.count, e.type, e.normalized, stride, (void*)offset);
		glEnableVertexAttribArray(e.index);
		offset += e.getSize();
	}
}

}
