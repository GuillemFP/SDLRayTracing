#include "CheckerTexture.h"

#include "Globals.h"
#include "HitInfo.h"

CheckerTexture::CheckerTexture(Texture* odd, Texture* even, const Vector3& dimensions) : _odd(odd), _even(even), _checkerDimensions(dimensions)
{
}

CheckerTexture::~CheckerTexture()
{
	RELEASE(_odd);
	RELEASE(_even);
}

Vector3 CheckerTexture::GetColor(const HitInfo& hitInfo, const Vector3& colorOdd, const Vector3& colorEven, const Vector3& dimensions)
{
	float sinus = math::Sin(dimensions.e[0] * hitInfo.point.e[0])*math::Sin(dimensions.e[1] * hitInfo.point.e[1])*math::Sin(dimensions.e[2] * hitInfo.point.e[2]);
	return sinus < 0 ? colorOdd : colorEven;
}

Vector3 CheckerTexture::GetColor(const HitInfo& hitInfo) const
{
	return GetColor(hitInfo, _odd->GetColor(hitInfo), _even->GetColor(hitInfo), _checkerDimensions);
}
