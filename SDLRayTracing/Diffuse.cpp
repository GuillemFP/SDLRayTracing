#include "Diffuse.h"

#include "HitInfo.h"
#include "Math.h"
#include "MathUtils.h"
#include "ScatterInfo.h"

Diffuse::Diffuse(const Vector3& albedo) : Material(Material::Type::Diffuse), _albedo(albedo)
{
}

Diffuse::~Diffuse()
{
}

bool Diffuse::Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const
{
	scatterInfo.reflects = true;

	Vector3 sphereTarget = hitInfo.point + hitInfo.normal + MathUtils::RandomPointInSphere(randomGenerator);
	scatterInfo.reflectedRay.pos = hitInfo.point;
	scatterInfo.reflectedRay.dir = normalize(sphereTarget - hitInfo.point);
	scatterInfo.attenuation = _albedo;

	return true;
}
