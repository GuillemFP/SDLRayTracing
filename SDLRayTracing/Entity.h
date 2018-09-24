#ifndef ENTITY_H
#define ENTITY_H

#include "Globals.h"
#include "Math.h"
#include <vector>

class Ray;
struct HitInfo;
struct ScatterInfo;

class Material;
class Shape;	

class Entity
{
public:
	Entity(Shape* shape, Material* material, const Vector3& position = Vector3::zero, const Vector3& rotation = Vector3::zero, const Vector3& scale = Vector3::one);
	Entity() {}
	~Entity();

	bool Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const;
	bool Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const;
	const AABB& GetBoundingBox() const { return _boundingBox; }
	const Vector3& GetEmissive(const HitInfo& hitInfo) const;

protected:
	AABB _boundingBox;
	Material* _material = nullptr;
	Shape* _shape = nullptr;
	math::float4x4 _transform;
	math::float4x4 _inverseTransform;
};

using VEntity = std::vector<Entity*>;
using AEntity = Entity**;

#endif // !ENTITY_H