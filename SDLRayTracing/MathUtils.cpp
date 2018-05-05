#include "MathUtils.h"

#include "Math.h"

namespace MathUtils
{
	math::float3 RandomPointInDisk(math::LCG& randomGenerator)
	{
		math::float3 ret;
		do
		{
			ret = 2.0f * math::float3(randomGenerator.Float(), randomGenerator.Float(), 0.0f) - math::float3(1.0f, 1.0f, 0.0f);
		} while (ret.Dot(ret) >= 1.0f);
		return ret;
	}
	
	math::float3 RandomPointInSphere(math::LCG& randomGenerator)
	{
		math::float3 ret;
		do
		{
			ret = 2.0f * math::float3(randomGenerator.Float(), randomGenerator.Float(), randomGenerator.Float()) - math::float3::one;
		} while (ret.LengthSq() >= 1.0f);
		return ret;
	}

	math::float3 ReflectedVector(const math::float3& inVector, const math::float3& normal)
	{
		return inVector - 2.0f * inVector.Dot(normal) * normal;
	}
}