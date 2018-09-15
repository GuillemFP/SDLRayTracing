#include "Diffuse.h"

#include "Globals.h"
#include "HitInfo.h"
#include "Math.h"
#include "MathUtils.h"
#include "ScatterInfo.h"
#include "Texture.h"

Diffuse::Diffuse(Texture* texture) : Material(Material::Type::Diffuse), _texture(texture)
{
}

Diffuse::~Diffuse()
{
	RELEASE(_texture);
}

bool Diffuse::Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const
{
	scatterInfo.reflects = true;

	Vector3 sphereTarget = hitInfo.point + hitInfo.normal + MathUtils::RandomPointInSphere(randomGenerator);
	scatterInfo.reflectedRay.pos = hitInfo.point;
	scatterInfo.reflectedRay.dir = normalize(sphereTarget - hitInfo.point);
	scatterInfo.attenuation = _texture->GetColor(hitInfo);

	return true;
}
