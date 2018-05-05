#ifndef ENTITYDATA_H
#define ENTITYDATA_H

#include "Entity.h"
#include "MaterialData.h"

struct EntityData
{
	Entity::Type type;
	Vector3 position;
	float radius = 1.0f;
	MaterialData materialData;
};

#endif // !ENTITYDATA_H