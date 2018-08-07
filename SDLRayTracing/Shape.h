#ifndef SHAPE_H
#define SHAPE_H

#include "Vector3.h"

class Ray;
class Material;
struct HitInfo;

class Shape
{
public:
	enum Type
	{
		Sphere = 0,
		Unknown
	};

	Shape(Type type, const Vector3& center);
	~Shape();

	virtual bool Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const = 0;

protected:
	Vector3 _center;

private:
	Type _type = Type::Unknown;
};

#endif // !SHAPE_H