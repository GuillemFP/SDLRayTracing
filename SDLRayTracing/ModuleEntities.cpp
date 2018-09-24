#include "ModuleEntities.h"

#include "Application.h"
#include "BvhNode.h"
#include "Config.h"
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
#include "TextureData.h"
#include "Plane.h"

ModuleEntities::ModuleEntities() : Module(MODULEENTITIES_NAME)
{
}

ModuleEntities::~ModuleEntities()
{
}

bool ModuleEntities::Init(Config* config)
{
	Config entities = Config(ENTITIES_CONFIGFILE);
	
	Config skybox = entities.GetSection("Skybox");
	_skybox = ParseUtils::ParseVector(skybox.GetArray("Color"));

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

#if USE_C_ARRAYS
	size_t numberOfEntities = _entities.size();
	_cEntities = new Entity*[numberOfEntities];
	for (size_t i = 0; i < numberOfEntities; i++)
	{
		_cEntities[i] = _entities.at(i);
	}
#endif // USE_C_ARRAYS

#if USE_BVH
	_rootNode = new BvhNode(_cEntities, numberOfEntities);
#endif // USE_BVH

	return true;
}

bool ModuleEntities::CleanUp()
{
	for (VEntity::reverse_iterator it = _entities.rbegin(); it != _entities.rend(); ++it)
		RELEASE(*it);

#if USE_C_ARRAYS
	RELEASE_ARRAY(_cEntities);
#endif // USE_C_ARRAYS

	return true;
}

void ModuleEntities::EntityFactory(const EntityData& data)
{
	Material* material = App->_materials->LoadMaterial(data.materialData);

	const ShapeData& shapeData = data.shapeData;
	Shape* shape = nullptr;

	switch (shapeData.type)
	{
	case Shape::Type::Sphere:
		shape = new Sphere(shapeData.radius);
		break;
	case Shape::Type::Plane:
		shape = new Plane(shapeData.dimensions);
	case Shape::Type::Unknown:
		APPLOG("Unknown shape in entity factory!");
		break;
	}

	if (!material || !shape)
	{
		return;
	}

	_entities.push_back(new Entity(shape, material, data.position, data.rotation));
}

Vector3 ModuleEntities::GetSkyboxColor(const HitInfo& hitInfo) const
{
	return _skybox;
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
	ShapeData& shapeData = entityData.shapeData;
	shapeData.radius = radius;
	shapeData.type = Shape::Type::Sphere;

	MaterialData& materialData = entityData.materialData;
	float materialProb = randomGenerator.Float();
	if (materialProb < diffuseProb)
	{
		materialData.type = Material::Type::Diffuse;
		TextureData& textureData = materialData.textureData;
		textureData.type = Texture::Type::Color;
		textureData.color = Vector3(randomGenerator.Float(), randomGenerator.Float(), randomGenerator.Float());
	}
	else if (materialProb < diffuseProb + metalProb)
	{
		materialData.type = Material::Type::Metal;
		materialData.fuzziness = randomGenerator.Float();

		TextureData& textureData = materialData.textureData;
		textureData.type = Texture::Type::Color;
		textureData.color = Vector3(randomGenerator.Float(), randomGenerator.Float(), randomGenerator.Float());
	}
	else
	{
		materialData.type = Material::Type::Dielectric;
		materialData.refractiveIndex = 1.0f + 0.5f * randomGenerator.Float();
	}
	EntityFactory(entityData);
}