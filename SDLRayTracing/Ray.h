#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

class Ray
{
public:
	Ray() {}
	Ray(const Vector3& position, const Vector3& direction) : pos(position), dir(direction) {}
	Vector3 origin() const { return pos; }
	Vector3 direction() const { return dir; }
	Vector3 getPoint(float t) const { return pos + t*dir; }

	Vector3 pos;
	Vector3 dir;
};

#endif // !RAY_H