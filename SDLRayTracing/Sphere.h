#ifndef SPHERE_H
#define SPHERE_H

#include "Entity.h"
#include "Vector3.h"

class Sphere : public Entity
{
public:
	Sphere(Material* material, float radius, const Vector3& center);
	~Sphere();

	bool Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const;
	float GetRadius() const;

protected:
	Vector3 GetNormal(const Vector3& surfacePoint) const;
	bool CheckRoot(const Ray& ray, float root, float minDistance, float maxDistance, HitInfo& hitInfo) const;

private:
	float _radius = 1.0f;
};

#endif // !SPHERE_H