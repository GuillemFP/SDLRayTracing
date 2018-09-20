#include "ImageTexture.h"

#include "Globals.h"
#include "ImageData.h"
#include "HitInfo.h"
#include <algorithm>

ImageTexture::ImageTexture(const ImageData& data) : _tex(data.tex), _nx(data.nx), _ny(data.ny)
{
}

ImageTexture::~ImageTexture()
{
}

Vector3 ImageTexture::GetColor(const HitInfo& hitInfo) const
{
	int i = _nx * hitInfo.u;
	int j = _ny * (1.0f - hitInfo.v) - 0.001f;
	i = std::min(_nx - 1, std::max(0, i));
	j = std::min(_ny - 1, std::max(0, j));
	float r = int(_tex[3 * i + 3 * _nx*j]) / 255.0f;
	float g = int(_tex[3 * i + 3 * _nx*j + 1]) / 255.0f;
	float b = int(_tex[3 * i + 3 * _nx*j + 2]) / 255.0f;
	return Vector3(r, g, b);
}
