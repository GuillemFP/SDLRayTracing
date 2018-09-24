#include "Plane.h"

#include "HitInfo.h"
#include "MathUtils.h"

Plane::Plane(const Vector3& dimensions) : Shape(Type::Plane), _dimensions(dimensions)
{
}

Plane::~Plane()
{
}

bool Plane::Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const
{
	return MathUtils::PlaneHit(ray, minDistance, maxDistance, hitInfo, _dimensions, 0.0f, 0, 1, 2, true);
}

AABB Plane::CreateBoundingBox() const
{
	const float halfWidth = 0.5f * _dimensions.e[0];
	const float halfHeight = 0.5f * _dimensions.e[1];
	return AABB(Vector3(-halfWidth, -halfHeight, 0.0f), Vector3(halfWidth, halfHeight, 0.0f));
}