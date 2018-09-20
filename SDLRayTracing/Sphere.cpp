#include "Sphere.h"

#include "HitInfo.h"
#include "Math.h"
#include "Globals.h"

namespace
{
	inline float GetSphereU(const Vector3& p)
	{
		float phi = atan2(p.e[2], p.e[0]);
		return 1.0f - (phi + PI) / (2.0f * PI);
	}

	inline float GetSphereV(const Vector3& p)
	{
		float theta = asin(p.e[1]);
		return (theta + 0.5f * PI) / PI;
	}

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
		Vector3 transformPoint = (hitInfo.point - _center) / _radius;
		hitInfo.u = GetSphereU(transformPoint);
		hitInfo.v = GetSphereV(transformPoint);
		return true;
	}

	float positiveRoot = (-b + squaredDiscriminant) / a;
	if (positiveRoot < maxDistance && positiveRoot > minDistance)
	{
		hitInfo.distance = positiveRoot;
		hitInfo.point = ray.getPoint(positiveRoot);
		hitInfo.normal = GetNormal(hitInfo.point, _center, _radius);
		Vector3 transformPoint = (hitInfo.point - _center) / _radius;
		hitInfo.u = GetSphereU(transformPoint);
		hitInfo.v = GetSphereV(transformPoint);
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