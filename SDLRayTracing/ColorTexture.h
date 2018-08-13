#ifndef COLORTEXTURE_H
#define COLORTEXTURE_H

#include "Texture.h"

class ColorTexture : public Texture
{
public:
	ColorTexture() = default;
	ColorTexture(const Vector3& color) : _color(color) {}

	virtual Vector3 GetColor() const { return _color; }

protected:
	Vector3 _color;
};

#endif // !COLORTEXTURE_H