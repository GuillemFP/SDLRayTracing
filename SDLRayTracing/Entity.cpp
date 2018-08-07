#include "Entity.h"

#include "Globals.h"
#include "HitInfo.h"
#include "Material.h"
#include "Math.h"
#include "Shape.h"

Entity::Entity(Shape* shape, Material* material) : _shape(shape), _material(material)
{
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
		hitInfo.material = _material;
		hitInfo.isHit = true;
		return true;
	}

	return false;
}