#ifndef ENTITY_H
#define ENTITY_H

#include "Vector3.h"

class Ray;
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

	virtual bool Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const = 0;
	Type GetType() const;

protected:
	virtual Vector3 GetNormal(const Vector3& surfacePoint) const = 0;

	Material* _material = nullptr;

private:
	Type _type = Type::Unknown;
};

#endif // !ENTITY_H