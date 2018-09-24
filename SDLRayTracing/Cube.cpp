#include "Cube.h"

Cube::Cube(const Vector3& dimensions) : Shape(Type::Cube), _dimensions(dimensions)
{
}

Cube::~Cube()
{
}

bool Cube::Hit(const Ray & ray, float minDistance, float maxDistance, HitInfo & hitInfo) const
{
	return false;
}

AABB Cube::CreateBoundingBox() const
{
	return AABB();
}
