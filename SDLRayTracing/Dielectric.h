#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "Material.h"

class Dielectric : public Material
{
public:
	Dielectric(float refractiveIndex);
	~Dielectric();

	bool Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const;

private:
	float _refractiveIndex = 1.0f;
};



#endif // !DIELECTRIC_H