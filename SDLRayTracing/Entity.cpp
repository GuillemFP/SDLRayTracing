#include "Entity.h"

#include "Globals.h"
#include "HitInfo.h"
#include "Material.h"
#include "Math.h"
#include "Shape.h"
#include "EntityData.h"

Entity::Entity(Shape* shape, Material* material, const EntityData& data) 
: _shape(shape)
, _material(material)
, _isSolid(data.isSolid)
, _density(data.density)
{
	_boundingBox = _shape->CreateBoundingBox();
	math::float3 rotationEuler = data.rotation.toFloat3() * DEG_TO_RAD;
	math::Quat quaternion = math::Quat::FromEulerXYZ(rotationEuler[0], rotationEuler[1], rotationEuler[2]);
	_transform = math::float4x4::FromTRS(data.position.toFloat3(), quaternion, data.scale.toFloat3());
	_inverseTransform = _transform.Inverted();
}

Entity::~Entity()
{
	RELEASE(_shape);
	RELEASE(_material)
}

bool Entity::Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo, math::LCG& randomGenerator) const
{
	Ray transformedRay = _inverseTransform * ray;

	if (_isSolid)
	{
		// Solid shapes
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

	// Volumes - shapes as boundaries
	const float maxFloat = std::numeric_limits<float>::max();
	HitInfo info1, info2;
	if (_shape->Hit(transformedRay, -maxFloat, maxFloat, info1))
	{
		if (_shape->Hit(transformedRay, info1.distance + 0.0001, maxFloat, info2))
		{
			if (info1.distance < minDistance) info1.distance = minDistance;
			if (info2.distance > maxDistance) info2.distance = maxDistance;
			if (info1.distance >= info2.distance) return false;
			if (info1.distance < 0) info1.distance = 0;

			const float distanceInBoundary = (info2.distance - info1.distance) * transformedRay.dir.length();
			const float hitDistance = -(1.0f / _density) * log(randomGenerator.Float());
			if (hitDistance < distanceInBoundary)
			{
				hitInfo.distance = info1.distance + hitDistance / transformedRay.dir.length();
				hitInfo.point = _transform.MulPos(transformedRay.getPoint(hitInfo.distance).toFloat3());
				hitInfo.normal = Vector3(1.0f, 0.0f, 0.0f);
				hitInfo.entity = this;
				hitInfo.isHit = true;
				return true;
			}
		}
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
