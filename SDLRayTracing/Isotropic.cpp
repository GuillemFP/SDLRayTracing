#include "Isotropic.h"

#include "Globals.h"
#include "HitInfo.h"
#include "MathUtils.h"
#include "Texture.h"
#include "ScatterInfo.h"

Isotropic::Isotropic(Texture* texture) : Material(Material::Type::Isotropic), _texture(texture)
{
}

Isotropic::~Isotropic()
{
	RELEASE(_texture);
}

bool Isotropic::Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const
{
	scatterInfo.reflects = true;

	scatterInfo.reflectedRay.pos = hitInfo.point;
	scatterInfo.reflectedRay.dir = MathUtils::RandomPointInSphere(randomGenerator).normalized();
	scatterInfo.attenuation = _texture->GetColor(hitInfo);

	return true;
}
