#ifndef CUBE_H
#define CUBE_H

#include "Shape.h"

class Cube : public Shape
{
public:
	Cube(const Vector3& dimensions);
	~Cube();

	bool Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const;

	AABB CreateBoundingBox() const;

private:
	Vector3 _dimensions;
};

#endif // !CUBE_H