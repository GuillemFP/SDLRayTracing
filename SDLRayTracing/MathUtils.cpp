#include "MathUtils.h"

#include "Math.h"

namespace MathUtils
{
	math::float3 RandomPointInSphere(math::LCG& randomGenerator)
	{
		math::float3 ret;
		do
		{
			ret = 2.0f * math::float3(randomGenerator.Float(), randomGenerator.Float(), randomGenerator.Float()) - math::float3::one;
		} while (ret.DistanceSq(math::float3::zero) >= 1.0f);
		return ret;
	}

	math::float3 reflectedVector(const math::float3& inVector, const math::float3& normal)
	{
		return inVector - 2.0f * inVector.Dot(normal) * normal;
	}
}