#include "DiffuseLight.h"

#include "Texture.h"

DiffuseLight::DiffuseLight(Texture* texture) : Material(Material::Type::DiffuseEmisive), _texture(texture)
{
}

DiffuseLight::~DiffuseLight()
{
}

bool DiffuseLight::Scatter(const Ray & ray, const HitInfo & hitInfo, ScatterInfo & scatterInfo, math::LCG & randomGenerator) const
{
	return false;
}

Vector3 DiffuseLight::Emitted(const HitInfo & hitInfo) const
{
	return _texture->GetColor(hitInfo);
}
