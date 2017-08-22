#pragma once

#include "id/Types.h"
#include "id/Math.h"

namespace Idol
{

enum class ETextureWrap
{
	Repeat,
	MirrorRepeat,
	ClampToEdge,
	ClampToBorder
};

enum class ETextureFilter
{
	Linear,
	Nearest,
	NearestMipmapLinear,
	NearestMipmapNearest,
	LinearMipmapLinear,
	LinearMipmapNearest
};

class Texture
{
private:
	int width;
	int height;
	int channels;

	uint texture;
	Texture(int width, int height, int channels, byte* data);
	
	uint wrappingModeToOpenGL(ETextureWrap wrappingMode);
	uint textureFilterToOpenGL(ETextureFilter filter);

	public:
	static Texture* createFromFile(const String& path);
	virtual ~Texture();
	void bind(int8 activeTexture = -1) const;

	void setWrappingMode(ETextureWrap wrappingMode);
	void setBorderColor(const math::vec4& color);

	void setMagFilter(ETextureFilter filter);
	void setMinFilter(ETextureFilter filter);

};

}