#ifndef AABB_H
#define AABB_H

#include "Vector3.h"

class Ray;

class AABB
{
public:
	AABB() = default;
	AABB(const Vector3& min, const Vector3& max);

	const Vector3& GetMin() const { return _min; }
	const Vector3& GetMax() const { return _max; }

	bool Hit(const Ray& ray, const float minDistance, const float maxDistance) const;

	static AABB SurroundingBox(const AABB& b1, const AABB& b2);

private:
	Vector3 _min;
	Vector3 _max;
};

#endif // !AABB_H