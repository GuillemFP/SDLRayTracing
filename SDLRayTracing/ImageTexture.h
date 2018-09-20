#ifndef IMAGETEXTURE_H
#define IMAGETEXTURE_H

#include "Texture.h"

struct ImageData;

class ImageTexture : public Texture
{
public:
	ImageTexture(const ImageData& data);
	~ImageTexture();

	Vector3 GetColor(const HitInfo& hitInfo) const;

private:
	unsigned char* _tex = nullptr;
	int _nx = 0;
	int _ny = 0;
};

#endif // !IMAGETEXTURE_H