#ifndef SHAPE_H
#define SHAPE_H

#include "Vector3.h"
#include "AABB.h"

class Ray;
class Material;
struct HitInfo;
struct ShapeData;

class Shape
{
public:
	enum Type
	{
		Sphere = 0,
		Plane,
		Unknown
	};

	Shape(Type type);
	~Shape();

	virtual bool Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const = 0;

	virtual AABB CreateBoundingBox() const = 0;

private:
	Type _type = Type::Unknown;
};

#endif // !SHAPE_H