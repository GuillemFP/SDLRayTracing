#ifndef ENTITY_H
#define ENTITY_H

#include "Vector3.h"

class Ray;
class Material;
class Shape;
struct HitInfo;

class Entity
{
public:
	Entity(Shape* shape, Material* material);
	~Entity();

	bool Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const;

protected:
	Material* _material = nullptr;
	Shape* _shape = nullptr;
};

#endif // !ENTITY_H