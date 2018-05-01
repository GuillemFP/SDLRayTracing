#include "Dielectric.h"

#include "HitInfo.h"
#include "Math.h"
#include "MathUtils.h"
#include "ScatterInfo.h"

namespace
{
	//Snell's law vectorial form
	// v_refract = r v + (r c - sqrt(1 - r^2 (1 - c^2))) n
	// r = n1/n2, c = - n * v
	bool refracts(const math::float3& inVector, const math::float3& normal, float refractionFactorRatio, math::float3& refracted)
	{
		float c = -normal.Dot(inVector);
		float discriminant = 1 - refractionFactorRatio * refractionFactorRatio * (1 - c * c);
		if (discriminant < 0)
		{
			//Total internal reflection
			return false;
		}

		refracted = refractionFactorRatio * inVector + (refractionFactorRatio * c - sqrt(discriminant)) * normal;
		return true;
	}
}

Dielectric::Dielectric(float refractiveIndex) : Material(Material::Type::Dielectric), _refractiveIndex(refractiveIndex)
{
}

Dielectric::~Dielectric()
{
}

bool Dielectric::Scatter(const math::Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const
{
	math::float3 normal;
	float refractionFactorRatio;

	// Negative value means ray crossing dielectric from inside to outside
	if (ray.dir.Dot(hitInfo.normal) <= 0)
	{
		normal = hitInfo.normal;
		refractionFactorRatio = 1.0f / _refractiveIndex;
	}
	else
	{
		normal = -hitInfo.normal;
		refractionFactorRatio = _refractiveIndex;
	}

	math::float3 refracted;
	scatterInfo.scatters = true;
	scatterInfo.attenuation = math::float3::one;
	scatterInfo.scatteredRay.pos = hitInfo.point;
	if (refracts(ray.dir, normal, refractionFactorRatio, refracted))
	{
		scatterInfo.scatteredRay.dir = refracted;
	}
	else
	{
		scatterInfo.scatteredRay.dir = MathUtils::reflectedVector(ray.dir, hitInfo.normal);
	}

	return true;
}

