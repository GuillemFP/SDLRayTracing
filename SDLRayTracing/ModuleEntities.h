#ifndef MODULEENTITIES_H
#define MODULEENTITIES_H

#define MODULEENTITIES_NAME "ModuleEntities"

#include "Module.h"
#include <vector>

namespace math
{
	class Ray;
}

class Entity;

class ModuleEntities : public Module
{
public:
	ModuleEntities();
	~ModuleEntities();

	bool Init();
	bool CleanUp();

	bool Hit(const math::Ray& ray) const;

private:
	std::vector<Entity*> _entities;
};

#endif // !MODULEENTITIES_H