#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "id/OpenGL.h"
#include "id/utils/VFS.h"
#include "id/Common.h"

namespace Idol
{

Texture::Texture(int width, int height, int channels, byte* data) : width(width), height(height), channels(channels)
{
	glGenTextures(1, &texture);
	bind();

	setWrappingMode(ETextureWrap::Repeat);

	setMagFilter(ETextureFilter::Linear);
	setMinFilter(ETextureFilter::Linear);

	if(channels == 3)
	{
		//RGB image
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		//RGBA image
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}

	glGenerateMipmap(GL_TEXTURE_2D);
}

uint Texture::wrappingModeToOpenGL(ETextureWrap wrappingMode)
{
	switch(wrappingMode)
	{
	case ETextureWrap::Repeat: 
		return GL_REPEAT;
	case ETextureWrap::MirrorRepeat:
		return GL_MIRRORED_REPEAT;
	case ETextureWrap::ClampToEdge:
		return GL_CLAMP_TO_EDGE;
	case ETextureWrap::ClampToBorder:
		return GL_CLAMP_TO_BORDER;
	default:
		return 0;
	}
}

uint Texture::textureFilterToOpenGL(ETextureFilter filter)
{
	switch(filter)
	{
	case ETextureFilter::Linear:
		return GL_LINEAR;
	case ETextureFilter::Nearest:
		return GL_NEAREST;
	case ETextureFilter::NearestMipmapLinear:
		return GL_NEAREST_MIPMAP_LINEAR;
	case ETextureFilter::NearestMipmapNearest:
		return GL_NEAREST_MIPMAP_NEAREST;
	case ETextureFilter::LinearMipmapLinear:
		return GL_LINEAR_MIPMAP_LINEAR;
	case ETextureFilter::LinearMipmapNearest: 
		return GL_LINEAR_MIPMAP_NEAREST;
	default:
		return 0;
	}
}

Texture* Texture::createFromFile(const String& path)
{
	String physicalPath = VFS::resolve(path);

	int width, height, channels;
	byte* data = stbi_load(physicalPath.c_str(), &width, &height, &channels, 0);
	if(!data)
	{
		ERROR("\nCould not open texture '" + path + "'");
	}

	Texture* texture = new Texture(width, height, channels, data);
	
	stbi_image_free(data);
	return texture;
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}

void Texture::bind(int8 activeTexture) const
{
	if(activeTexture >= 0)
	{
		glActiveTexture(GL_TEXTURE0 + activeTexture);
	}

	glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::setWrappingMode(ETextureWrap wrappingMode)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrappingModeToOpenGL(wrappingMode));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrappingModeToOpenGL(wrappingMode));
}

void Texture::setBorderColor(const math::vec4& color)
{
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &color[0]);
}

void Texture::setMagFilter(ETextureFilter filter)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilterToOpenGL(filter));
}

void Texture::setMinFilter(ETextureFilter filter)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilterToOpenGL(filter));
}
}
