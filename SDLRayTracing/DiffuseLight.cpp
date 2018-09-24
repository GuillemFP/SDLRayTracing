#include "DiffuseLight.h"

#include "Texture.h"

DiffuseLight::DiffuseLight(Texture* texture) : Material(Material::Type::DiffuseEmisive), _texture(texture)
{
}

DiffuseLight::~DiffuseLight()
{
}

Vector3 DiffuseLight::Emitted(const HitInfo & hitInfo) const
{
	return _texture->GetColor(hitInfo);
}
