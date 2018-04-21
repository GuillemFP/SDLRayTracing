#include "Entity.h"

#include "HitInfo.h"
#include "Math.h"

bool Entity::Hit(const math::Ray& ray, HitInfo& hitInfo) const
{
	float t = RayHitLength(ray);
	if (t < 0.0f)
	{
		return false;
	}

	hitInfo.point = ray.GetPoint(t);
	hitInfo.normal = GetNormal(hitInfo.point);

	return true;
}

EntityType Entity::GetType() const
{
	return _type;
}