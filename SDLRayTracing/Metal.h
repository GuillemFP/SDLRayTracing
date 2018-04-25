#ifndef METAL_H
#define METAL_H

#include "Material.h"
#include "MathGeoLib\include\Math\float3.h"

class Metal : public Material
{
public:
	Metal(const math::float3& albedo);
	~Metal();

	bool Scatter(const math::Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const;

private:
	math::float3 _albedo;
};

#endif // !METAL_H