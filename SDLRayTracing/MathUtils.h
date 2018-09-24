#ifndef MATHUTILS_H
#define MATHUTILS_H

#include "Vector3.h"
#include "MathGeoLib\include\Algorithm\Random\LCG.h"

struct HitInfo;
class Ray;

namespace MathUtils
{
	Vector3 RandomPointInSphere(math::LCG& randomGenerator);
	Vector3 RandomPointInDisk(math::LCG& randomGenerator);
	Vector3 ReflectedVector(const Vector3& inVector, const Vector3& normal);
	bool PlaneHit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo, const float planeWidth, const float planeHeight, const float planePosition, const int planeCoord0, const int planeCoord1, const int depthCoord, const bool positiveNormal);
}

#endif // !MATHUTILS_H
