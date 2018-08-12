#include "Shape.h"

#include "ShapeData.h"
#include "Sphere.h"

Shape::Shape(Type type, const Vector3& center) : _type(type), _center(center)
{
}

Shape::~Shape()
{
}

bool Shape::Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo, const ShapeData& shapeData)
{
	switch (shapeData.type)
	{
	case Type::Sphere:
		return Sphere::Hit(ray, minDistance, maxDistance, hitInfo, shapeData.position, shapeData.radius);
	}
}

AABB Shape::CreateBoundingBox(const ShapeData& shapeData)
{
	switch (shapeData.type)
	{
	case Type::Sphere:
		return Sphere::CreateBoundingBox(shapeData.position, shapeData.radius);
	}
}