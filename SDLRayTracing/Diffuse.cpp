#include "Diffuse.h"

#include "HitInfo.h"
#include "Math.h"

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

Diffuse::Diffuse(const math::float3& albedo) : Material(Material::Type::Diffusive), _albedo(albedo)
{
}

Diffuse::~Diffuse()
{
}

bool Diffuse::Hit(const math::Ray& ray, const HitInfo& hitInfo, math::float3& attenuation, math::Ray& reflectedRay, math::LCG& randomGenerator) const
{
	math::float3 sphereTarget = hitInfo.point + hitInfo.normal + RandomPointInSphere(randomGenerator);
	reflectedRay = math::Ray(hitInfo.point, (sphereTarget - hitInfo.point).Normalized());
	attenuation = _albedo;

	return true;
}
