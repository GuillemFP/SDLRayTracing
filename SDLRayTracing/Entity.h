#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

class Ray;
class Material;
class Shape;
struct HitInfo;

class Entity
{
public:
	Entity(Shape* shape, Material* material);
	~Entity();

	bool Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const;

protected:
	Material* _material = nullptr;
	Shape* _shape = nullptr;
};

using VEntity = std::vector<Entity*>;

#endif // !ENTITY_H