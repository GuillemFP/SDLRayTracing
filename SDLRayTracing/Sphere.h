#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"
#include "Vector3.h"

class Sphere : public Shape
{
public:
	Sphere(float radius);
	~Sphere();

	bool Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const;

	AABB CreateBoundingBox() const;

	float GetRadius() const;

private:
	float _radius = 1.0f;
};

#endif // !SPHERE_H