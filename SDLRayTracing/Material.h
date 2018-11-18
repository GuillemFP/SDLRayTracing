#ifndef MATERIAL_H
#define MATERIAL_H

#include "Vector3.h"

namespace math
{
	class LCG;
}

class Ray;
struct HitInfo;
struct ScatterInfo;
struct MaterialData;

class Material
{
public:
	enum Type
	{
		Diffuse = 0,
		DiffuseEmisive,
		Metal,
		Dielectric,
		Isotropic,
		Unknown
	};

	Material(Type type) : _type(type) {}
	~Material() = default;

	Type GetType() const
	{
		return _type;
	}

	virtual bool Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const = 0;
	virtual Vector3 Emitted(const HitInfo& hitInfo) const { return Vector3::zero; }

private:
	Type _type = Unknown;
};

#endif // !MATERIAL_H