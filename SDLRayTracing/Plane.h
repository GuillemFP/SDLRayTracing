#ifndef PLANE_H
#define PLANE_H

#include "Shape.h"
#include "Vector3.h"

class Plane : public Shape
{
public:
	Plane(const Vector3& dimensions);
	~Plane();

	bool Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const;

	AABB CreateBoundingBox() const;

private:
	Vector3 _dimensions;
};

#endif // !PLANE_H