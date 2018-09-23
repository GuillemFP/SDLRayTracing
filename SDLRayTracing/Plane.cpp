#include "Plane.h"

#include "HitInfo.h"

Plane::Plane(const Vector3& dimensions) : Shape(Type::Plane), _dimensions(dimensions)
{
}

Plane::~Plane()
{
}

bool Plane::Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const
{
	const float t = -ray.pos.z() / ray.dir.z();
	if (t < minDistance || t > maxDistance)
		return false;

	const float x = ray.pos.x() + t * ray.dir.x();
	const float y = ray.pos.y() + t * ray.dir.y();
	const float halfWidth = 0.5f * _dimensions.e[0];
	const float halfHeight = 0.5f * _dimensions.e[1];
	if (x < -halfWidth || x > halfWidth || y < -halfHeight || y > halfHeight)
		return false;

	hitInfo.point = ray.getPoint(t);
	hitInfo.distance = t;
	hitInfo.normal = Vector3(0.0f, 0.0f, 1.0f);
	hitInfo.u = (x - halfWidth) / _dimensions.e[0];
	hitInfo.v = (y - halfHeight) / _dimensions.e[1];
	return true;
}

AABB Plane::CreateBoundingBox() const
{
	const float halfWidth = 0.5f * _dimensions.e[0];
	const float halfHeight = 0.5f * _dimensions.e[1];
	return AABB(Vector3(-halfWidth, -halfHeight, 0.0f), Vector3(halfWidth, halfHeight, 0.0f));
}