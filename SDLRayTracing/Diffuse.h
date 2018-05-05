#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "Material.h"
#include "Vector3.h"

class Diffuse : public Material
{
public:
	Diffuse(const Vector3& albedo);
	~Diffuse();

	bool Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const;

private:
	Vector3 _albedo;
};

#endif // !DIFFUSE_H