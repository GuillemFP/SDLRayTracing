#ifndef MATERIAL_H
#define MATERIAL_H

namespace math
{
	class LCG;
}

class Ray;
class Vector3;
struct HitInfo;
struct ScatterInfo;
struct MaterialData;

class Material
{
public:
	enum Type
	{
		Diffuse = 0,
		Metal,
		Dielectric,
		Unknown
	};

	Material(Type type) : _type(type) {}
	~Material() = default;

	Type GetType() const
	{
		return _type;
	}

	virtual bool Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const = 0;

private:
	Type _type = Unknown;
};

#endif // !MATERIAL_H