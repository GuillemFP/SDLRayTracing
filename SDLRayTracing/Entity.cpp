#include "Entity.h"

#include "Globals.h"
#include "HitInfo.h"
#include "Math.h"

Entity::Entity(Type type, Material* material, const Vector3& center) : _type(type), _material(material), _center(center)
{
}

Entity::~Entity()
{
	RELEASE(_material)
}

const Vector3& Entity::GetCenter() const
{
	return _center;
}

Entity::Type Entity::GetType() const
{
	return _type;
}