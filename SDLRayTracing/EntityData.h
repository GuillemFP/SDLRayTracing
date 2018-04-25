#ifndef ENTITYDATA_H
#define ENTITYDATA_H

#include "Entity.h"
#include "MaterialData.h"

class Config;

struct EntityData
{
	Entity::Type type;
	math::float3 position;
	float radius = 1.0f;
	MaterialData materialData;
};

namespace EntityDataUtils
{
	EntityData parseEntityData(const Config& config);
	Entity::Type typeFromString(const std::string& type);
}

#endif // !ENTITYDATA_H