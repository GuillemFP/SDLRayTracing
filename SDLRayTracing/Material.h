#ifndef MATERIAL_H
#define MATERIAL_H

namespace math
{
	class Ray;
	class float3;
	class LCG;
}

struct HitInfo;

class Material
{
public:
	enum Type
	{
		Diffusive = 0,
		Unknown
	};

	Material(Type type) : _type(type) {}
	~Material() = default;

	Type GetType() const
	{
		return _type;
	}

	virtual bool Hit(const math::Ray& ray, const HitInfo& hitInfo, math::float3& attenuation, math::Ray& reflectedRay, math::LCG& randomGenerator) const = 0;

private:
	Type _type = Unknown;
};

#endif // !MATERIAL_H