#ifndef ENTITY_H
#define ENTITY_H

#include "Globals.h"
#include "AABB.h"
#include <vector>

namespace math
{
	class LCG;
}

class Ray;
struct HitInfo;
struct ScatterInfo;

class Material;
class Shape;	

class Entity
{
public:
	Entity(Shape* shape, Material* material);
	Entity() {}
	~Entity();

	bool Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const;
	bool Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const;
	const AABB& GetBoundingBox() const { return _boundingBox; }

protected:
	AABB _boundingBox;
	Material* _material = nullptr;
	Shape* _shape = nullptr;
};

using VEntity = std::vector<Entity*>;
using AEntity = Entity**;

#endif // !ENTITY_H