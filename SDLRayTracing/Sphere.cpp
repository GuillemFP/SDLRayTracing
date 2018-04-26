#include "Sphere.h"

#include "Math.h"

Sphere::Sphere(Material* material, float radius, const math::float3& center) : Entity(Type::Sphere, material), _radius(radius), _center(center)
{
}

Sphere::~Sphere()
{
}

float Sphere::RayHitLength(const math::Ray& ray, float minDistance, float maxDistance) const
{
	math::float3 oc = ray.pos - _center;
	float a = ray.dir.Dot(ray.dir);
	float b = oc.Dot(ray.dir);
	float c = oc.Dot(oc) - _radius*_radius;
	float discriminant = b*b - a*c;
	if (discriminant < 0.0f)
	{
		//No real solution -> no hit
		return -1.0f;
	}

	float squaredDiscriminant = sqrt(discriminant);
	float negativeRoot = (-b - squaredDiscriminant) / a;
	if (negativeRoot < maxDistance && negativeRoot > minDistance)
	{
		return negativeRoot;
	}

	float positiveRoot = (-b + squaredDiscriminant) / a;
	if (positiveRoot < maxDistance && positiveRoot > minDistance)
	{
		return positiveRoot;
	}

	return -1.0f;
}

math::float3 Sphere::GetNormal(const math::float3& surfacePoint) const
{
	return (surfacePoint - _center).Normalized();
}