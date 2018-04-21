#ifndef SPHERE_H
#define SPHERE_H

#include "Entity.h"
#include "MathGeoLib\include\Math\float3.h";

class Sphere : public Entity
{
public:
	Sphere(float radius, const math::float3& center);
	~Sphere();

protected:
	float RayHitLength(const math::Ray& ray) const;

private:
	float _radius = 1.0f;
	math::float3 _center;
};

#endif // !SPHERE_H