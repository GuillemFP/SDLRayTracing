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

bool Sphere::Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo, const Vector3& center, const float radius)
{
	Vector3 oc = ray.pos - center;
	float a = dot(ray.dir, ray.dir);
	float b = dot(oc, ray.dir);
	float c = dot(oc, oc) - radius*radius;
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
		hitInfo.normal = GetNormal(hitInfo.point, center, radius);
		return true;
	}

	float positiveRoot = (-b + squaredDiscriminant) / a;
	if (positiveRoot < maxDistance && positiveRoot > minDistance)
	{
		hitInfo.distance = positiveRoot;
		hitInfo.point = ray.getPoint(positiveRoot);
		hitInfo.normal = GetNormal(hitInfo.point, center, radius);
		return true;
	}

	return false;
}

bool Sphere::Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const
{
	return Hit(ray, minDistance, maxDistance, hitInfo, _center, _radius);
}

AABB Sphere::CreateBoundingBox(const Vector3& center, const float radius)
{
	Vector3 radiusDisplacement(radius, radius, radius);
	return AABB(center - radiusDisplacement, center + radiusDisplacement);
}

AABB Sphere::CreateBoundingBox() const
{
	return CreateBoundingBox(_center, _radius);
}

float Sphere::GetRadius() const
{
	return _radius;
}