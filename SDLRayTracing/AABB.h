#ifndef AABB_H
#define AABB_H

#include "Vector3.h"
#include "Ray.h"

class AABB
{
public:
	AABB() = default;
	AABB(const Vector3& min, const Vector3& max);

	const Vector3& GetMin() const { return _min; }
	const Vector3& GetMax() const { return _max; }

	inline bool Hit(const Ray& ray, const float minDistance, const float maxDistance) const;

	static AABB SurroundingBox(const AABB& b1, const AABB& b2);

private:
	Vector3 _min;
	Vector3 _max;
};

inline bool AABB::Hit(const Ray & ray, const float minDistance, const float maxDistance) const
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

#endif // !AABB_H