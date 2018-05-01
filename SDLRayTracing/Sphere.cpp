#include "Sphere.h"

#include "HitInfo.h"
#include "Math.h"

Sphere::Sphere(Material* material, float radius, const math::float3& center) : Entity(Type::Sphere, material), _radius(radius), _center(center)
{
}

Sphere::~Sphere()
{
}

bool Sphere::Hit(const math::Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const
{
	math::float3 oc = ray.pos - _center;
	float a = ray.dir.Dot(ray.dir);
	float b = oc.Dot(ray.dir);
	float c = oc.Dot(oc) - _radius*_radius;
	float discriminant = b*b - a*c;
	if (discriminant <= 0.0f)
	{
		//No real solution -> no hit
		return false;
	}

	float squaredDiscriminant = sqrt(discriminant);
	float negativeRoot = (-b - squaredDiscriminant) / a;
	if (CheckRoot(ray, negativeRoot, minDistance, maxDistance, hitInfo))
	{
		return true;
	}

	float positiveRoot = (-b + squaredDiscriminant) / a;
	if (CheckRoot(ray, positiveRoot, minDistance, maxDistance, hitInfo))
	{
		return true;
	}

	return false;
}

bool Sphere::CheckRoot(const math::Ray& ray, float root, float minDistance, float maxDistance, HitInfo& hitInfo) const
{
	if (root < maxDistance && root > minDistance)
	{
		hitInfo.distance = root;
		hitInfo.point = ray.GetPoint(root);
		hitInfo.normal = GetNormal(hitInfo.point);
		hitInfo.isHit = true;
		hitInfo.material = _material;
		return true;
	}

	return false;
}

math::float3 Sphere::GetNormal(const math::float3& surfacePoint) const
{
	return (surfacePoint - _center) / _radius;
}