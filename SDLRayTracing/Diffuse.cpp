#include "Diffuse.h"

#include "HitInfo.h"
#include "Math.h"
#include "ScatterInfo.h"

namespace
{
	math::float3 RandomPointInSphere(math::LCG& randomGenerator)
	{
		math::float3 ret;
		do
		{
			ret = 2.0f * math::float3(randomGenerator.Float(), randomGenerator.Float(), randomGenerator.Float()) - math::float3::one;
		} 
		while (ret.DistanceSq(math::float3::zero) >= 1.0f);
		return ret;
	}
}

Diffuse::Diffuse(const math::float3& albedo) : Material(Material::Type::Diffuse), _albedo(albedo)
{
}

Diffuse::~Diffuse()
{
}

bool Diffuse::Scatter(const math::Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const
{
	scatterInfo.scatters = true;

	math::float3 sphereTarget = hitInfo.point + hitInfo.normal + RandomPointInSphere(randomGenerator);
	scatterInfo.scatteredRay.pos = hitInfo.point;
	scatterInfo.scatteredRay.dir = (sphereTarget - hitInfo.point).Normalized();
	scatterInfo.attenuation = _albedo;

	return scatterInfo.scatters;
}
