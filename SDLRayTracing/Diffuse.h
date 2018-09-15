#ifndef DIFFUSE_H
#define DIFFUSE_H

#include "Material.h"
#include "Vector3.h"

class Texture;

class Diffuse : public Material
{
public:
	Diffuse(Texture* texture);
	~Diffuse();

	bool Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const;

private:
	Texture* _texture;
};

#endif // !DIFFUSE_H