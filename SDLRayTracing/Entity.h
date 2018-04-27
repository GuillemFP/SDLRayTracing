#ifndef ENTITY_H
#define ENTITY_H

#include "MathGeoLib\include\Math\float3.h"

namespace math
{
	class Ray;
}

class Material;
struct HitInfo;

class Entity
{
public:
	enum Type
	{
		Sphere = 0,
		Unknown
	};

	Entity(Type type, Material* material);
	~Entity();

	virtual bool Hit(const math::Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const = 0;
	Type GetType() const;

protected:
	virtual math::float3 GetNormal(const math::float3& surfacePoint) const = 0;

	Material* _material = nullptr;

private:
	Type _type = Type::Unknown;
};

#endif // !ENTITY_H