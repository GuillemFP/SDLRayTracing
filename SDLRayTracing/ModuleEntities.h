#ifndef MODULEENTITIES_H
#define MODULEENTITIES_H

#define MODULEENTITIES_NAME "ModuleEntities"

#include "Module.h"
#include <vector>

class Entity;

class ModuleEntities : public Module
{
public:
	ModuleEntities();
	~ModuleEntities();

	bool Init();
	bool CleanUp();

private:
	std::vector<Entity*> _entities;
};

#endif // !MODULEENTITIES_H