#ifndef METAL_H
#define METAL_H

#include "Material.h"
#include "Vector3.h"

class Metal : public Material
{
public:
	Metal(const Vector3& albedo, float fuzziness);
	~Metal();

	static bool Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator, const Vector3& albedo, const float fuzziness);
	bool Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const;

private:
	Vector3 _albedo;
	float _fuzziness = 0.0f;
};

#endif // !METAL_H