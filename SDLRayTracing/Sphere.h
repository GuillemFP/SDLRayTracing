#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"
#include "Vector3.h"

class Sphere : public Shape
{
public:
	Sphere(float radius, const Vector3& center);
	~Sphere();

	inline static bool Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo, const Vector3& center, const float radius);
	bool Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const;
	float GetRadius() const;

private:
	float _radius = 1.0f;
};

#endif // !SPHERE_H