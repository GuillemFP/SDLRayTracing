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
class BvhNode;
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
	Vector3 GetSkyboxColor(const HitInfo& hitInfo) const;

	void EntityFactory(const EntityData& data);

	const VEntity& GetEntities() const
	{
		return _entities;
	}

#if USE_C_ARRAYS
	const AEntity& GetDeviceEntities() const
	{
		return _cEntities;
	}

	size_t GetNumberOfEntities() const
	{
		return _entities.size();
	}
#endif // USE_C_ARRAYS

#if USE_BVH
	const BvhNode* GetBvhRootNode() const
	{
		return _rootNode;
	}
#endif // USE_BVH

private:
	void InitRandomSpheres();
	void InitRandomSphere(const Vector3& center, float radius, math::LCG& randomGenerator);

	void InitFloor();

	Vector3 _skybox = Vector3::zero;

	VEntity _entities;

#if USE_C_ARRAYS
	AEntity _cEntities;
#endif // USE_C_ARRAYS

#if USE_BVH
	BvhNode* _rootNode = nullptr;
#endif // USE_BVH
};

#endif // !MODULEENTITIES_H