#include "Dielectric.h"

#include "Globals.h"
#include "HitInfo.h"
#include "Math.h"
#include "MathUtils.h"
#include "ScatterInfo.h"

namespace
{
	float CosineIncidentAngle(const Vector3& normal, const Vector3& inVector)
	{
		return -dot(normal, inVector);
	}

	//Snell's law vectorial form
	// v_refract = r v + (r c - sqrt(1 - r^2 (1 - c^2))) n
	// r = n1/n2, c = - n * v
	bool Refracts(const Vector3& inVector, const Vector3& normal, float refractionFactorRatio, Vector3& refracted)
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

bool Dielectric::Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const
{
	Vector3 normal;
	float refractionFactorRatio;

	// Positive value means ray crossing dielectric from inside to outside
	if (dot(ray.dir, hitInfo.normal) > 0)
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

	Vector3 refracted;
	scatterInfo.attenuation = Vector3::one;
	if (Refracts(ray.dir, normal, refractionFactorRatio, refracted))
	{
		float reflectionCoefficient = SchlickApproximation(refractionFactorRatio, cosine);
#if DIELECTRIC_R_COEFFICIENT_PROBABILITY
		if (randomGenerator.Float() >= reflectionCoefficient)
		{
			scatterInfo.refracts = true;
			scatterInfo.refractedRay = Ray(hitInfo.point, refracted, ray.time);
			return true;
		}
#else
		scatterInfo.reflectionCoeff = reflectionCoefficient;

		scatterInfo.refracts = true;
		scatterInfo.refractionCoeff = 1.0f - reflectionCoefficient;
		scatterInfo.refractedRay = Ray(hitInfo.point, refracted, ray.time);
		if (scatterInfo.refractionCoeff >= 1.0f)
		{
			return true;
		}
#endif
	}

	scatterInfo.reflects = true;
	scatterInfo.reflectedRay = Ray(hitInfo.point, MathUtils::ReflectedVector(ray.dir, hitInfo.normal), ray.time);
	return true;
}

