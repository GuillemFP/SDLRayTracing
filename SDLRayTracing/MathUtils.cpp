#include "MathUtils.h"

#include "Math.h"
#include "HitInfo.h"

namespace MathUtils
{
	Vector3 RandomPointInDisk(math::LCG& randomGenerator)
	{
		Vector3 ret;
		do
		{
			ret = 2.0f * Vector3(randomGenerator.Float(), randomGenerator.Float(), 0.0f) - Vector3(1.0f, 1.0f, 0.0f);
		} while (dot(ret, ret) >= 1.0f);
		return ret;
	}
	
	Vector3 RandomPointInSphere(math::LCG& randomGenerator)
	{
		Vector3 ret;
		do
		{
			ret = 2.0f * Vector3(randomGenerator.Float(), randomGenerator.Float(), randomGenerator.Float()) - Vector3::one;
		} while (ret.lengthSq() >= 1.0f);
		return ret;
	}

	Vector3 ReflectedVector(const Vector3& inVector, const Vector3& normal)
	{
		return inVector - 2.0f * dot(inVector, normal) * normal;
	}

	bool PlaneHit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo, const float planeWidth, const float planeHeight, const float planePosition, const int planeCoord0, const int planeCoord1, const int depthCoord, const bool positiveNormal)
	{
		const float t = (planePosition - ray.pos.e[depthCoord]) / ray.dir.e[depthCoord];
		if (t < minDistance || t > maxDistance)
			return false;

		const float x = ray.pos.e[planeCoord0] + t * ray.dir.e[planeCoord0];
		const float y = ray.pos.e[planeCoord1] + t * ray.dir.e[planeCoord1];
		const float halfWidth = 0.5f * planeWidth;
		const float halfHeight = 0.5f * planeHeight;
		if (x < -halfWidth || x > halfWidth || y < -halfHeight || y > halfHeight)
			return false;

		hitInfo.point = ray.getPoint(t);
		hitInfo.distance = t;
		hitInfo.normal = Vector3::zero;
		hitInfo.normal.e[depthCoord] = positiveNormal ? 1.0f : -1.0f;
		hitInfo.u = (x - halfWidth) / planeWidth;
		hitInfo.v = (y - halfHeight) / planeHeight;
		return true;
	}
}