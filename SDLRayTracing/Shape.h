#ifndef SHAPE_H
#define SHAPE_H

#include "Vector3.h"

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
		Unknown
	};

	Shape(Type type, const Vector3& center);
	~Shape();

	static bool Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo, const ShapeData& shapeData);
	virtual bool Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const = 0;

protected:
	Vector3 _center;

private:
	Type _type = Type::Unknown;
};

#endif // !SHAPE_H