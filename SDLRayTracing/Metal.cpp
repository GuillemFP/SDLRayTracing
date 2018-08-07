#include "Metal.h"

#include "Globals.h"
#include "HitInfo.h"
#include "Math.h"
#include "MathUtils.h"
#include "ScatterInfo.h"

Metal::Metal(const Vector3& albedo, float fuzziness) : Material(Material::Type::Metal), _albedo(albedo), _fuzziness(fuzziness)
{
}

Metal::~Metal()
{
}

bool Metal::Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator, const Vector3& albedo, const float fuzziness)
{
	scatterInfo.reflectedRay.pos = hitInfo.point;

	Vector3 scatteredRay = MathUtils::ReflectedVector(ray.dir, hitInfo.normal) + fuzziness * MathUtils::RandomPointInSphere(randomGenerator);
	scatterInfo.reflectedRay.dir = normalize(scatteredRay);
	scatterInfo.attenuation = albedo;

	scatterInfo.reflects = dot(scatterInfo.reflectedRay.dir, hitInfo.normal) > 0;
	return scatterInfo.reflects;
}

bool Metal::Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const
{
	return Scatter(ray, hitInfo, scatterInfo, randomGenerator, _albedo, _fuzziness);
}