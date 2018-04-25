#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "Material.h"
#include "MathGeoLib\include\Math\float3.h"


class Diffuse : public Material
{
public:
	Diffuse(const math::float3& albedo);
	~Diffuse();

	bool Hit(const math::Ray& ray, const HitInfo& hitInfo, math::float3& attenuation, math::Ray& scatteredRay, math::LCG& randomGenerator) const;

private:
	math::float3 _albedo;
};

#endif // !DIFFUSE_H