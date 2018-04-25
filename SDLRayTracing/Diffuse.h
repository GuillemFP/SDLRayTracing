#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "Material.h"
#include "MathGeoLib\include\Math\float3.h"

class Diffuse : public Material
{
public:
	Diffuse(const math::float3& albedo);
	~Diffuse();

	bool Scatter(const math::Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const;

private:
	math::float3 _albedo;
};

#endif // !DIFFUSE_H