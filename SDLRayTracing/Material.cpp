#include "Material.h"

#include "MaterialData.h"
#include "Dielectric.h"
#include "Diffuse.h"
#include "Metal.h"

bool Material::Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator, const MaterialData& materialData)
{
	switch (materialData.type)
	{
	case Type::Dielectric:
		return Dielectric::Scatter(ray, hitInfo, scatterInfo, randomGenerator, materialData.refractiveIndex);
	case Type::Diffuse:
		return Diffuse::Scatter(ray, hitInfo, scatterInfo, randomGenerator, Texture::GetColor(hitInfo, materialData.textureData));
	case Type::Metal:
		return Metal::Scatter(ray, hitInfo, scatterInfo, randomGenerator, Texture::GetColor(hitInfo, materialData.textureData), materialData.fuzziness);
	}
}