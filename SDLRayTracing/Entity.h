#ifndef ENTITY_H
#define ENTITY_H

#include "MathGeoLib\include\Math\float3.h"

namespace math
{
	class Ray;
}

struct HitInfo;

enum class EntityType
{
	Sphere,
	Unknown
};

class Entity
{
public:
	Entity(EntityType type) : _type(type) {}
	~Entity() = default;

	bool Hit(const math::Ray& ray, HitInfo& hitInfo) const;
	EntityType GetType() const;

protected:
	virtual float RayHitLength(const math::Ray& ray) const = 0;
	//virtual math::float3 GetNormal(const math::float3& surfacePoint) const = 0;

private:
	EntityType _type = EntityType::Unknown;
};

#endif // !ENTITY_H