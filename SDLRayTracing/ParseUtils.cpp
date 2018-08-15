#include "ParseUtils.h"

#include "Globals.h"
#include "Config.h"
#include "Math.h"

namespace ParseUtils
{
	math::float3 ParseFloat3(const ConfigArray& config, const math::float3& defaultValue)
	{
		math::float3 vector;

		vector.x = config.GetFloat(0, defaultValue.x);
		vector.y = config.GetFloat(1, defaultValue.y);
		vector.z = config.GetFloat(2, defaultValue.z);

		return vector;
	}

	Vector3 ParseVector(const ConfigArray& config, const Vector3& defaultValue)
	{
		return ParseFloat3(config, defaultValue.toFloat3());
	}

	EntityData ParseEntityData(const Config& config)
	{
		EntityData data;

		data.shapeData = ParseShapeData(config.GetSection("Shape"));
		data.materialData = ParseMaterialData(config.GetSection("Material"));

		return data;
	}

	ShapeData ParseShapeData(const Config& config)
	{
		ShapeData data;

		data.type = ParseShapeTypeFromString(config.GetStringRequired("Type"));
		data.position = ParseVector(config.GetArray("Position"));
		data.radius = config.GetFloat("Radius", 1.0f);

		return data;
	}

	Shape::Type ParseShapeTypeFromString(const std::string& type)
	{
		if (type == "Sphere")
			return Shape::Type::Sphere;

		APPLOG("Invalid entity type");

		return Shape::Type::Unknown;
	}

	MaterialData ParseMaterialData(const Config& config)
	{
		MaterialData data;

		data.type = ParseMaterialTypeFromString(config.GetStringRequired("Type"));
		if (config.HasSection("Texture"))
			data.textureData = ParseTextureData(config.GetSection("Texture"));
		else
			data.textureData.type = Texture::Type::NoTexture;
		data.fuzziness = config.GetFloat("Fuzziness", 0.0f);
		data.refractiveIndex = config.GetFloat("RefractiveIndex", 1.0f);

		return data;
	}

	Material::Type ParseMaterialTypeFromString(const std::string& type)
	{
		if (type == "Diffuse")
			return Material::Type::Diffuse;
		if (type == "Metal")
			return Material::Type::Metal;
		if (type == "Dielectric")
			return Material::Type::Dielectric;

		APPLOG("Invalid material type");

		return Material::Type::Unknown;
	}

	TextureData ParseTextureData(const Config& config)
	{
		TextureData data;

		data.type = ParseTextureTypeFromString(config.GetStringRequired("Type"));
		data.color = ParseVector(config.GetArray("Color"));
		if (config.HasArray("Dimensions"))
			data.dimensions = ParseVector(config.GetArray("Dimensions"));
		if (config.HasArray("SubTextures"))
		{
			ConfigArray subTextures = config.GetArray("SubTextures");
			for (size_t i = 0; i < subTextures.GetArrayLength(); i++)
			{
				Config subTexture = subTextures.GetSection(i);
				data.subTextures.push_back(ParseTextureData(subTexture));
			}
		}

		return data;
	}

	Texture::Type ParseTextureTypeFromString(const std::string& type)
	{
		if (type == "Color")
			return Texture::Type::Color;
		if (type == "Checker")
			return Texture::Type::Checker;

		return Texture::Type::NoTexture;
	}
}