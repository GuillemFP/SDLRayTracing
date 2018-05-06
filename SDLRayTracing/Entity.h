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

	Entity(Type type, Material* material, const Vector3& center);
	~Entity();

	virtual bool Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const = 0;
	const Vector3& GetCenter() const;
	Type GetType() const;

protected:
	Material* _material = nullptr;
	Vector3 _center;

private:
	Type _type = Type::Unknown;
};

#endif // !ENTITY_H