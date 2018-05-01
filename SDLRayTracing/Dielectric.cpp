#include "Dielectric.h"

#include "HitInfo.h"
#include "Math.h"
#include "MathUtils.h"
#include "ScatterInfo.h"

namespace
{
	float CosineIncidentAngle(const math::float3& normal, const math::float3& inVector)
	{
		return -normal.Dot(inVector);
	}

	//Snell's law vectorial form
	// v_refract = r v + (r c - sqrt(1 - r^2 (1 - c^2))) n
	// r = n1/n2, c = - n * v
	bool Refracts(const math::float3& inVector, const math::float3& normal, float refractionFactorRatio, math::float3& refracted)
	{
		float c = CosineIncidentAngle(normal, inVector);
		float discriminant = 1 - refractionFactorRatio * refractionFactorRatio * (1 - c * c);
		if (discriminant < 0)
		{
			//Total internal reflection
			return false;
		}

		refracted = refractionFactorRatio * inVector + (refractionFactorRatio * c - sqrt(discriminant)) * normal;
		return true;
	}

	//Approximates reflection coefficient as function of incident angle
	float SchlickApproximation(float refractionFactorRatio, float cosine)
	{
		float r0 = (refractionFactorRatio - 1.0f) / (refractionFactorRatio + 1.0f);
		r0 = r0 * r0;
		return r0 + (1.0f - r0) * math::Pow(1.0f - cosine, 5);
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

	// Positive value means ray crossing dielectric from inside to outside
	if (ray.dir.Dot(hitInfo.normal) > 0)
	{
		normal = -hitInfo.normal;
		refractionFactorRatio = _refractiveIndex;	
	}
	else
	{
		normal = hitInfo.normal;
		refractionFactorRatio = 1.0f / _refractiveIndex;
	}
	float cosine = CosineIncidentAngle(normal, ray.dir);

	math::float3 refracted;
	scatterInfo.scatters = true;
	scatterInfo.attenuation = math::float3::one;
	if (Refracts(ray.dir, normal, refractionFactorRatio, refracted))
	{
		float reflectionProbability = SchlickApproximation(refractionFactorRatio, cosine);
		if (randomGenerator.Float() >= reflectionProbability)
		{
			scatterInfo.scatteredRay = math::Ray(hitInfo.point, refracted);
			return true;
		}
	}

	scatterInfo.scatteredRay = math::Ray(hitInfo.point, MathUtils::ReflectedVector(ray.dir, hitInfo.normal));
	return true;
}

