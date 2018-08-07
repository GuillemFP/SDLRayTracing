#ifndef MODULEENTITIES_H
#define MODULEENTITIES_H

#define MODULEENTITIES_NAME "ModuleEntities"

#define ENTITIES_CONFIGFILE "scene.json"

#include "Module.h"
#include "Entity.h"
#include <vector>

namespace math
{
	class LCG;
}

class Vector3;
class Ray;
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

	void EntityFactory(const EntityData& data);

	const VEntity& GetEntities() const
	{
		return _entities;
	}

#if USE_CUDA
	const Entity* GetDeviceEntities() const
	{
		return _dEntities;
	}

	size_t GetNumberOfEntities() const
	{
		return _entities.size();
	}
#endif // USE_CUDA

private:
	void InitRandomSpheres();
	void InitRandomSphere(const Vector3& center, float radius, math::LCG& randomGenerator);

	VEntity _entities;

#if USE_CUDA
	Entity* _dEntities;
#endif // USE_CUDA
};

#endif // !MODULEENTITIES_H