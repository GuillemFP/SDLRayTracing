#include "Entity.h"

#include "Globals.h"
#include "HitInfo.h"
#include "Math.h"

Entity::Entity(Type type, Material* material) : _type(type), _material(material)
{
}

Entity::~Entity()
{
	RELEASE(_material)
}

Entity::Type Entity::GetType() const
{
	return _type;
}