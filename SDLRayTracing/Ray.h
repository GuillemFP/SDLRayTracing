#ifndef RAY_H
#define RAY_H

#include "Vector3.h"
#include "MathGeoLib\include\Math\float4x4.h"

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

inline Ray operator*(const math::float4x4& m, const Ray& r)
{
	return Ray(m.MulPos(r.pos.toFloat3()), m.MulDir(r.dir.toFloat3()).Normalized());
}

#endif // !RAY_H