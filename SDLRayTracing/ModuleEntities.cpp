#include "ModuleEntities.h"

#include "Entity.h"
#include "HitInfo.h"
#include "Sphere.h"

ModuleEntities::ModuleEntities() : Module(MODULEENTITIES_NAME)
{
}

ModuleEntities::~ModuleEntities()
{
}

bool ModuleEntities::Init()
{
	_entities.push_back(new Sphere(0.5f, math::float3(0.0f, 0.0f, -1.0f)));
	_entities.push_back(new Sphere(100.0f, math::float3(0.0f, -100.5f, -1.0f)));

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