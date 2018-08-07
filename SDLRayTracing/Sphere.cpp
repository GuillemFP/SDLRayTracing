#include "Sphere.h"

#include "HitInfo.h"
#include "Math.h"

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
		hitInfo.normal = GetNormal(hitInfo.point);
		return true;
	}

	float positiveRoot = (-b + squaredDiscriminant) / a;
	if (positiveRoot < maxDistance && positiveRoot > minDistance)
	{
		hitInfo.distance = positiveRoot;
		hitInfo.point = ray.getPoint(positiveRoot);
		hitInfo.normal = GetNormal(hitInfo.point);
		return true;
	}

	return false;
}

float Sphere::GetRadius() const
{
	return _radius;
}