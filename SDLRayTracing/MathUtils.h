#ifndef MATHUTILS_H
#define MATHUTILS_H

#include "MathGeoLib\include\Math\float3.h"
#include "MathGeoLib\include\Algorithm\Random\LCG.h"

namespace MathUtils
{
	math::float3 RandomPointInSphere(math::LCG& randomGenerator);
	math::float3 RandomPointInDisk(math::LCG& randomGenerator);
	math::float3 ReflectedVector(const math::float3& inVector, const math::float3& normal);
}

#endif // !MATHUTILS_H
