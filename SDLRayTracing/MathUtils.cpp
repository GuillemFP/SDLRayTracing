#include "MathUtils.h"

#include "Math.h"

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
}