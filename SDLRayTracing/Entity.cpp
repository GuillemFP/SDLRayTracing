#include "Entity.h"

#include "Globals.h"
#include "HitInfo.h"
#include "Material.h"
#include "Math.h"
#include "Shape.h"

Entity::Entity(Shape* shape, Material* material, const Vector3& position, const Vector3& rotation, const Vector3& scale) : _shape(shape), _material(material)
{
	_boundingBox = _shape->CreateBoundingBox();
	math::float3 rotationEuler = rotation.toFloat3() * DEG_TO_RAD;
	math::Quat quaternion = math::Quat::FromEulerXYZ(rotationEuler[0], rotationEuler[1], rotationEuler[2]);
	_transform = math::float4x4::FromTRS(position.toFloat3(), quaternion, scale.toFloat3());
	_inverseTransform = _transform.Inverted();
}

Entity::~Entity()
{
	RELEASE(_shape);
	RELEASE(_material)
}

bool Entity::Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const
{
	Ray transformedRay = _inverseTransform * ray;
	if (_shape->Hit(transformedRay, minDistance, maxDistance, hitInfo))
	{
		hitInfo.point = _transform.MulPos(hitInfo.point.toFloat3());
		hitInfo.normal = _transform.MulDir(hitInfo.normal.toFloat3()).Normalized();
		hitInfo.entity = this;
		hitInfo.isHit = true;
		return true;
	}

	return false;
}

bool Entity::Scatter(const Ray& ray, const HitInfo& hitInfo, ScatterInfo& scatterInfo, math::LCG& randomGenerator) const
{
	return _material->Scatter(ray, hitInfo, scatterInfo, randomGenerator);
}

const Vector3& Entity::GetEmissive(const HitInfo& hitInfo) const
{
	return _material->Emitted(hitInfo);
}
