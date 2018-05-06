#include "Sphere.h"

#include "HitInfo.h"
#include "Math.h"

Sphere::Sphere(Material* material, float radius, const Vector3& center) : Entity(Type::Sphere, material, center), _radius(radius)
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

bool Sphere::CheckRoot(const Ray& ray, float root, float minDistance, float maxDistance, HitInfo& hitInfo) const
{
	if (root < maxDistance && root > minDistance)
	{
		hitInfo.distance = root;
		hitInfo.point = ray.getPoint(root);
		hitInfo.normal = GetNormal(hitInfo.point);
		hitInfo.isHit = true;
		hitInfo.material = _material;
		return true;
	}

	return false;
}

Vector3 Sphere::GetNormal(const Vector3& surfacePoint) const
{
	return (surfacePoint - _center) / _radius;
}

float Sphere::GetRadius() const
{
	return _radius;
}