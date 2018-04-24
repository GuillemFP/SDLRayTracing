#include "ModuleEntities.h"

#include "Config.h"
#include "Entity.h"
#include "EntityData.h"
#include "HitInfo.h"
#include "Sphere.h"

ModuleEntities::ModuleEntities() : Module(MODULEENTITIES_NAME)
{
}

ModuleEntities::~ModuleEntities()
{
}

bool ModuleEntities::Init(Config* config)
{
	Config entities = Config(ENTITIES_CONFIGFILE);
	ConfigArray entitiesArray = entities.GetArray("Entities");

	for (int i = 0; i < entitiesArray.GetArrayLength(); i++)
	{
		EntityData data = EntityDataUtils::parseEntityData(entitiesArray.GetSection(i));
		EntityFactory(data);
	}

	return true;
}

bool ModuleEntities::CleanUp()
{
	for (std::vector<Entity*>::reverse_iterator it = _entities.rbegin(); it != _entities.rend(); ++it)
		RELEASE(*it);

	return true;
}

bool ModuleEntities::Hit(const math::Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const
{
	HitInfo currentHitInfo;
	float currentMaxDistance =  maxDistance;

	for (std::vector<Entity*>::const_iterator it = _entities.cbegin(); it != _entities.cend(); ++it)
	{
		if ((*it)->Hit(ray, minDistance, currentMaxDistance, currentHitInfo))
		{
			currentMaxDistance = currentHitInfo.distance;
			hitInfo = currentHitInfo;
		}
	}

	return hitInfo.isHit;
}

Entity* ModuleEntities::EntityFactory(const EntityData& data)
{
	static_assert(Entity::Type::Unknown == 1, "Update entity factory code");

	Entity* entity = nullptr;

	switch (data.type)
	{
	case Entity::Type::Sphere:
		entity = new Sphere(data.radius, data.position);
		break;
	}

	if (entity)
	{
		_entities.push_back(entity);
	}

	return entity;
}