#include "Sphere.h"

#include "Math.h"

Sphere::Sphere(float radius, const math::float3& center) : Entity(EntityType::Sphere), _radius(radius), _center(center)
{
}

Sphere::~Sphere()
{
}

float Sphere::RayHitLength(const math::Ray& ray) const
{
	math::float3 oc = ray.pos - _center;
	float a = ray.dir.Dot(ray.dir);
	float b = 2.0f * oc.Dot(ray.dir);
	float c = oc.Dot(oc) - _radius*_radius;
	float discriminant = b*b - 4 * a*c;
	if (discriminant < 0.0f)
	{
		//No real solution -> no hit
		return -1.0f;
	}

	return (-b - sqrt(discriminant)) / (2.0f * a);
}