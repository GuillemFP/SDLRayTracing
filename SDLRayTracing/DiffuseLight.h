#ifndef DIFFUSELIGHT_H
#define DIFFUSELIGHT_H

#include "Material.h"

class Texture;

class DiffuseLight : public Material
{
public:
	DiffuseLight(Texture* texture);
	~DiffuseLight();

	Vector3 Emitted(const HitInfo& hitInfo) const;

private:
	Texture* _texture;
};

#endif // !DIFFUSELIGHT_H