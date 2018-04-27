#include "Metal.h"

#include "Globals.h"
#include "HitInfo.h"
#include "Math.h"
#include "MathUtils.h"
#include "ScatterInfo.h"

Metal::Metal(const math::float3& albedo, float fuzziness) : Material(Material::Type::Metal), _albedo(albedo), _fuzziness(fuzziness)
{
}

Metal::~Metal()
{
}

bool Metal::Scatter(const math::Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const
{
	scatterInfo.scatteredRay.pos = hitInfo.point;

	math::float3 scatteredRay = MathUtils::reflectedVector(ray.dir, hitInfo.normal) + _fuzziness * MathUtils::RandomPointInSphere(randomGenerator);
	scatterInfo.scatteredRay.dir = scatteredRay.Normalized();
	scatterInfo.attenuation = _albedo;

	scatterInfo.scatters = scatterInfo.scatteredRay.dir.Dot(hitInfo.normal) > 0;
	return scatterInfo.scatters;
}