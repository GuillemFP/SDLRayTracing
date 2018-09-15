#include "Entity.h"

#include "Globals.h"
#include "HitInfo.h"
#include "Material.h"
#include "Math.h"
#include "Shape.h"

Entity::Entity(Shape* shape, Material* material) : _shape(shape), _material(material)
{
	_boundingBox = _shape->CreateBoundingBox();
}

Entity::~Entity()
{
	RELEASE(_shape);
	RELEASE(_material)
}

bool Entity::Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const
{
	if (_shape->Hit(ray, minDistance, maxDistance, hitInfo))
	{
		hitInfo.entity = this;
		hitInfo.isHit = true;
		return true;
	}

	return false;
}

bool Entity::Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const
{
	return _material->Scatter(ray, hitInfo, scatterInfo, randomGenerator);
}
