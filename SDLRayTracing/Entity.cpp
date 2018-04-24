#include "Entity.h"

#include "HitInfo.h"
#include "Math.h"

bool Entity::Hit(const math::Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const
{
	hitInfo.distance = RayHitLength(ray);
	if (hitInfo.distance < 0.0f || hitInfo.distance > maxDistance)
	{
		return false;
	}

	hitInfo.point = ray.GetPoint(hitInfo.distance);
	hitInfo.normal = GetNormal(hitInfo.point);
	hitInfo.isHit = true;

	return true;
}

Entity::Type Entity::GetType() const
{
	return _type;
}