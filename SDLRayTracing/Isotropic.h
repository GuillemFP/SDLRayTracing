#ifndef ISOTROPIC_H
#define ISOTROPIC_H

#include "Material.h"
#include "Vector3.h"

class Texture;

class Isotropic : public Material
{
public:
	Isotropic(Texture* texture);
	~Isotropic();

	bool Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const;

private:
	Texture* _texture;
};

#endif // !ISOTROPIC_H