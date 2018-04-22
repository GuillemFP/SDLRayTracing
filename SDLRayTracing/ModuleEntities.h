#ifndef MODULEENTITIES_H
#define MODULEENTITIES_H

#define MODULEENTITIES_NAME "ModuleEntities"

#define ENTITIES_CONFIGFILE "scene.json"

#include "Module.h"
#include <vector>

namespace math
{
	class Ray;
}

class Entity;
struct HitInfo;

class ModuleEntities : public Module
{
public:
	ModuleEntities();
	~ModuleEntities();

	bool Init(Config* config = nullptr);
	bool CleanUp();

	bool Hit(const math::Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const;

private:
	std::vector<Entity*> _entities;
};

#endif // !MODULEENTITIES_H