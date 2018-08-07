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
#include "Shape.h"

#include <cuda_runtime_api.h>
#include <cuda.h>

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

#if USE_CUDA
	size_t size = _entities.size() * sizeof(Entity);

	cudaMalloc((void **)&_dEntities, size);
#endif // USE_CUDA

	return true;
}

bool ModuleEntities::CleanUp()
{
	for (std::vector<Entity*>::reverse_iterator it = _entities.rbegin(); it != _entities.rend(); ++it)
		RELEASE(*it);

#if USE_CUDA
	cudaFree(_dEntities);
#endif // USE_CUDA

	return true;
}

Entity* ModuleEntities::EntityFactory(const EntityData& data)
{
	Material* material = App->_materials->LoadMaterial(data.materialData);

	const ShapeData& shapeData = data.shapeData;
	Shape* shape = nullptr;

	switch (shapeData.type)
	{
	case Shape::Type::Sphere:
		shape = new Sphere(shapeData.radius, shapeData.position);
		break;
	}

	if (!material || !shape)
	{
		return nullptr;
	}

	Entity* entity = new Entity(shape, material);
	_entities.push_back(entity);

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
	ShapeData& shapeData = entityData.shapeData;
	shapeData.position = center;
	shapeData.radius = radius;
	shapeData.type = Shape::Type::Sphere;

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