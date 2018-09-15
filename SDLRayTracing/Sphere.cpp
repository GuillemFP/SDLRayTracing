#include "Sphere.h"

#include "HitInfo.h"
#include "Math.h"

namespace
{
	inline Vector3 GetNormal(const Vector3& surfacePoint, const Vector3& center, const float radius)
	{
		return (surfacePoint - center) / radius;
	}
}

Sphere::Sphere(float radius, const Vector3& center) : Shape(Type::Sphere, center), _radius(radius)
{
}

Sphere::~Sphere()
{
}

bool Sphere::Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const
{
	Vector3 oc = ray.pos - _center;
	float a = dot(ray.dir, ray.dir);
	float b = dot(oc, ray.dir);
	float c = dot(oc, oc) - _radius*_radius;
	float discriminant = b*b - a*c;
	if (discriminant <= 0.0f)
	{
		//No real solution -> no hit
		return false;
	}

	float squaredDiscriminant = sqrt(discriminant);
	float negativeRoot = (-b - squaredDiscriminant) / a;
	if (negativeRoot < maxDistance && negativeRoot > minDistance)
	{
		hitInfo.distance = negativeRoot;
		hitInfo.point = ray.getPoint(negativeRoot);
		hitInfo.normal = GetNormal(hitInfo.point, _center, _radius);
		return true;
	}

	float positiveRoot = (-b + squaredDiscriminant) / a;
	if (positiveRoot < maxDistance && positiveRoot > minDistance)
	{
		hitInfo.distance = positiveRoot;
		hitInfo.point = ray.getPoint(positiveRoot);
		hitInfo.normal = GetNormal(hitInfo.point, _center, _radius);
		return true;
	}

	return false;
}

AABB Sphere::CreateBoundingBox() const
{
	Vector3 radiusDisplacement(_radius, _radius, _radius);
	return AABB(_center - radiusDisplacement, _center + radiusDisplacement);
}

float Sphere::GetRadius() const
{
	return _radius;
}