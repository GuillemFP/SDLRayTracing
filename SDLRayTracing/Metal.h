#ifndef METAL_H
#define METAL_H

#include "Material.h"
#include "Vector3.h"

class Texture;

class Metal : public Material
{
public:
	Metal(Texture* texture, float fuzziness);
	~Metal();

	bool Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const;

private:
	Texture* _texture;
	float _fuzziness = 0.0f;
};

#endif // !METAL_H