#ifndef DIFFUSELIGHT_H
#define DIFFUSELIGHT_H

#include "Material.h"

class Texture;

class DiffuseLight : public Material
{
public:
	DiffuseLight(Texture* texture);
	~DiffuseLight();

	bool Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const;
	Vector3 Emitted(const HitInfo& hitInfo) const;

private:
	Texture* _texture;
};

#endif // !DIFFUSELIGHT_H