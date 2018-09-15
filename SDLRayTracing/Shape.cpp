#include "Shape.h"

#include "ShapeData.h"
#include "Sphere.h"

Shape::Shape(Type type, const Vector3& center) : _type(type), _center(center)
{
}

Shape::~Shape()
{
}