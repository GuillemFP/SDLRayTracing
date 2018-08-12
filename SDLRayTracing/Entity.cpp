#include "Entity.h"

#include "Globals.h"
#include "HitInfo.h"
#include "Material.h"
#include "Math.h"
#include "Shape.h"

#if USE_OOP
	Entity::Entity(Shape* shape, Material* material) : _shape(shape), _material(material)
	{
	}
#else
	Entity::Entity(const ShapeData& shapeData, const MaterialData& materialData) : _shapeData(shapeData), _materialData(materialData)
	{
	}
#endif // USE_OOP

Entity::~Entity()
{
#if USE_OOP
	RELEASE(_shape);
	RELEASE(_material)
#endif // !USE_OOP
}

bool Entity::Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const
{
#if USE_OOP
	if (_shape->Hit(ray, minDistance, maxDistance, hitInfo))
#else
	if (Shape::Hit(ray, minDistance, maxDistance, hitInfo, _shapeData))
#endif // USE_OOP
	{
		hitInfo.entity = this;
		hitInfo.isHit = true;
		return true;
	}

	return false;
}

bool Entity::Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const
{
#if USE_OOP
	return _material->Scatter(ray, hitInfo, scatterInfo, randomGenerator);
#else
	return Material::Scatter(ray, hitInfo, scatterInfo, randomGenerator, _materialData);
#endif // USE_OOP
}

#if !USE_OOP
	Entity Entity::Clone() const
	{
		return Entity(_shapeData, _materialData);
	}
#endif // !USE_OOP
