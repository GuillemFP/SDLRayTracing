#ifndef CHECKERTEXTURE_H
#define CHECKERTEXTURE_H

#include "Texture.h"

class CheckerTexture : public Texture
{
public:
	CheckerTexture(Texture* odd, Texture* even, const Vector3& dimensions);
	~CheckerTexture();

	static Vector3 GetColor(const HitInfo& hitInfo, const Vector3& colorOdd, const Vector3& colorEven, const Vector3& dimensions);
	virtual Vector3 GetColor(const HitInfo& hitInfo) const;

private:
	Texture* _odd = nullptr;
	Texture* _even = nullptr;
	Vector3 _checkerDimensions = Vector3::one;
};

#endif // !CHECKERTEXTURE_H