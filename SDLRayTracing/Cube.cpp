#include "Cube.h"

#include "MathUtils.h"
#include "HitInfo.h"

Cube::Cube(const Vector3& dimensions) : Shape(Type::Cube), _dimensions(dimensions)
{
}

Cube::~Cube()
{
}

bool Cube::Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const
{
	float currentMaxDistance = maxDistance;
	bool isHit = false;
	if (MathUtils::PlaneHit(ray, minDistance, currentMaxDistance, hitInfo, _dimensions, 0.5f * _dimensions.z(), 0, 1, 2, true))
	{
		isHit = true;
		currentMaxDistance = hitInfo.distance;
	}
	if (MathUtils::PlaneHit(ray, minDistance, currentMaxDistance, hitInfo, _dimensions, - 0.5f * _dimensions.z(), 0, 1, 2, false))
	{
		isHit = true;
		currentMaxDistance = hitInfo.distance;
	}
	if (MathUtils::PlaneHit(ray, minDistance, currentMaxDistance, hitInfo, _dimensions, 0.5f * _dimensions.x(), 1, 2, 0, true))
	{
		isHit = true;
		currentMaxDistance = hitInfo.distance;
	}
	if (MathUtils::PlaneHit(ray, minDistance, currentMaxDistance, hitInfo, _dimensions, -0.5f * _dimensions.x(), 1, 2, 0, false))
	{
		isHit = true;
		currentMaxDistance = hitInfo.distance;
	}
	if (MathUtils::PlaneHit(ray, minDistance, currentMaxDistance, hitInfo, _dimensions, 0.5f * _dimensions.y(), 2, 0, 1, true))
	{
		isHit = true;
		currentMaxDistance = hitInfo.distance;
	}
	if (MathUtils::PlaneHit(ray, minDistance, currentMaxDistance, hitInfo, _dimensions, -0.5f * _dimensions.y(), 2, 0, 1, false))
	{
		isHit = true;
		currentMaxDistance = hitInfo.distance;
	}

	return isHit;
}

AABB Cube::CreateBoundingBox() const
{
	const float halfWidth = 0.5f * _dimensions.e[0];
	const float halfHeight = 0.5f * _dimensions.e[1];
	const float halfDepth = 0.5f * _dimensions.e[2];

	Vector3 min(-halfWidth, -halfHeight, -halfDepth);
	Vector3 max(halfWidth, halfHeight, halfDepth);
	return AABB(min, max);
}
