#include "ModuleEntities.h"

#include "Entity.h"
#include "Sphere.h"

ModuleEntities::ModuleEntities() : Module(MODULEENTITIES_NAME)
{
}

ModuleEntities::~ModuleEntities()
{
}

bool ModuleEntities::Init()
{
	Sphere* sphere = new Sphere(0.5f, math::float3(1.0f, 0.0f, -4.0f));
	_entities.push_back(sphere);

	return true;
}

bool ModuleEntities::CleanUp()
{
	for (std::vector<Entity*>::reverse_iterator it = _entities.rbegin(); it != _entities.rend(); ++it)
		RELEASE(*it);

	return true;
}

bool ModuleEntities::Hit(const math::Ray& ray) const
{
	for (std::vector<Entity*>::const_iterator it = _entities.cbegin(); it != _entities.cend(); ++it)
	{
		if ((*it)->Hit(ray))
		{
			return true;
		}
	}

	return false;
}