#include "AABB.h"

#include "Ray.h"

AABB::AABB(const Vector3 & min, const Vector3 & max) : _min(min), _max(max)
{
}

bool AABB::Hit(const Ray & ray, const float minDistance, const float maxDistance) const
{
	for (size_t i = 0; i < 3; i++)
	{
		float invD = 1.0f / ray.dir[i];
		float t0 = (_min[i] - ray.pos[i]) * invD;
		float t1 = (_max[i] - ray.pos[i]) * invD;
		if (invD < 0.0f)
		{
			std::swap(t0, t1);
		}
		const float tMin = t0 > minDistance ? t0 : minDistance;
		const float tMax = t1 < maxDistance ? t1 : maxDistance;
		if (tMax <= tMin)
			return false;
	}

	return true;
}

AABB AABB::SurroundingBox(const AABB& b1, const AABB& b2)
{
	Vector3 b1Min = b1.GetMin();
	Vector3 b2Min = b2.GetMin();

	Vector3 small(fmin(b1Min[0], b2Min[0]), fmin(b1Min[1], b2Min[1]), fmin(b1Min[2], b2Min[2]));

	Vector3 b1Max = b1.GetMax();
	Vector3 b2Max = b2.GetMax();

	Vector3 large(fmax(b1Max[0], b2Max[0]), fmax(b1Max[1], b2Max[1]), fmax(b1Max[2], b2Max[2]));

	return AABB(small, large);
}

