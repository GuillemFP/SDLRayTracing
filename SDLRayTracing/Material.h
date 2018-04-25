#ifndef MATERIAL_H
#define MATERIAL_H

namespace math
{
	class Ray;
	class float3;
	class LCG;
}

struct HitInfo;
struct ScatterInfo;

class Material
{
public:
	enum Type
	{
		Diffuse = 0,
		Unknown
	};

	Material(Type type) : _type(type) {}
	~Material() = default;

	Type GetType() const
	{
		return _type;
	}

	virtual bool Scatter(const math::Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const = 0;

private:
	Type _type = Unknown;
};

#endif // !MATERIAL_H