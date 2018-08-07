#ifndef MODULEENTITIES_H
#define MODULEENTITIES_H

#define MODULEENTITIES_NAME "ModuleEntities"

#define ENTITIES_CONFIGFILE "scene.json"

#include "Module.h"
#include <vector>

namespace math
{
	class LCG;
}

class Vector3;
class Ray;
class Entity;
struct EntityData;
struct HitInfo;

class ModuleEntities : public Module
{
public:
	ModuleEntities();
	~ModuleEntities();

	bool Init(Config* config = nullptr);
	bool CleanUp();

	bool Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const;

	Entity* EntityFactory(const EntityData& data);

private:
	void InitRandomSpheres();
	void InitRandomSphere(const Vector3& center, float radius, math::LCG& randomGenerator);

	std::vector<Entity*> _entities;

#if USE_CUDA_ENTITIES
	Entity* _dEntities;
#endif // USE_CUDA_ENTITIES
};

#endif // !MODULEENTITIES_H