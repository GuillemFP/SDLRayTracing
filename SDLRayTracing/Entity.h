#ifndef ENTITY_H
#define ENTITY_H

#include "Globals.h"
#include <vector>

namespace math
{
	class LCG;
}

class Ray;
struct HitInfo;
struct ScatterInfo;

#if USE_OOP
	class Material;
	class Shape;	
#else
	#include "MaterialData.h"
	#include "ShapeData.h"
#endif // USE_OOP

class Entity
{
public:
#if USE_OOP
	Entity(Shape* shape, Material* material);
#else
	Entity(const ShapeData& shapeData, const MaterialData& materialData);
	Entity() {}
#endif // USE_OOP
	~Entity();

	bool Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const;
	bool Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const;

#if USE_C_ARRAYS
	Entity Clone() const;
#endif // USE_C_ARRAYS

protected:
#if USE_OOP
	Material* _material = nullptr;
	Shape* _shape = nullptr;
#else
	ShapeData _shapeData;
	MaterialData _materialData;
#endif // USE_OOP
};

#if USE_OOP
	using VEntity = std::vector<Entity*>;
#else
	using VEntity = std::vector<Entity>;
#endif // USE_OOP

#endif // !ENTITY_H