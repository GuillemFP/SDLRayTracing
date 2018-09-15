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

Vector3 CheckerTexture::GetColor(const HitInfo& hitInfo) const
{
	float sinus = math::Sin(_checkerDimensions.e[0] * hitInfo.point.e[0])*math::Sin(_checkerDimensions.e[1] * hitInfo.point.e[1])*math::Sin(_checkerDimensions.e[2] * hitInfo.point.e[2]);
	return sinus < 0 ? _odd->GetColor(hitInfo) : _even->GetColor(hitInfo);
}
