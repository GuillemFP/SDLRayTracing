#include "ModuleEntities.h"

#include "Application.h"
#include "Config.h"
#include "Entity.h"
#include "EntityData.h"
#include "HitInfo.h"
#include "Material.h"
#include "MaterialData.h"
#include "Math.h"
#include "MathUtils.h"
#include "ModuleMaterials.h"
#include "ParseUtils.h"
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
		EntityData data = ParseUtils::ParseEntityData(entitiesArray.GetSection(i));
		EntityFactory(data);
	}

	if (config->GetBool("Add Random", false))
	{
		InitRandomSpheres();
	}

	return true;
}

bool ModuleEntities::CleanUp()
{
	for (std::vector<Entity*>::reverse_iterator it = _entities.rbegin(); it != _entities.rend(); ++it)
		RELEASE(*it);

	return true;
}

bool ModuleEntities::Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const
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

	Material* material = App->_materials->LoadMaterial(data.materialData);

	Entity* entity = nullptr;

	switch (data.type)
	{
	case Entity::Type::Sphere:
		entity = new Sphere(material, data.radius, data.position);
		break;
	}

	if (entity)
	{
		_entities.push_back(entity);
	}

	return entity;
}

void ModuleEntities::InitRandomSpheres()
{
	math::LCG randomGenerator;
	const float radius = 0.2f;
	
	for (int x = -5; x < 10; x++)
	{
		for (int z = -5; z < 0; z++)
		{
			Vector3 center(x + 0.9f * randomGenerator.Float(), radius, z + 0.9f * randomGenerator.Float());
			InitRandomSphere(center, radius, randomGenerator);
		}
		for (int z = 1; z < 6; z++)
		{
			Vector3 center(x + 0.9f * randomGenerator.Float(), radius, z + 0.9f * randomGenerator.Float());
			InitRandomSphere(center, radius, randomGenerator);
		}
	}
}

void ModuleEntities::InitRandomSphere(const Vector3& center, float radius, math::LCG& randomGenerator)
{
	const float diffuseProb = 0.8f;
	const float metalProb = 0.15f;

	EntityData entityData;
	entityData.position = center;
	entityData.radius = radius;
	entityData.type = Entity::Sphere;

	MaterialData& materialData = entityData.materialData;
	float materialProb = randomGenerator.Float();
	if (materialProb < diffuseProb)
	{
		materialData.type = Material::Type::Diffuse;
		materialData.albedo = Vector3(randomGenerator.Float(), randomGenerator.Float(), randomGenerator.Float());
	}
	else if (materialProb < diffuseProb + metalProb)
	{
		materialData.type = Material::Type::Metal;
		materialData.albedo = Vector3(randomGenerator.Float(), randomGenerator.Float(), randomGenerator.Float());
		materialData.fuzziness = randomGenerator.Float();
	}
	else
	{
		materialData.type = Material::Type::Dielectric;
		materialData.refractiveIndex = 1.0f + 0.5f * randomGenerator.Float();
	}
	EntityFactory(entityData);
}