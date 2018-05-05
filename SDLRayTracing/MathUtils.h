#ifndef MATHUTILS_H
#define MATHUTILS_H

#include "Vector3.h"
#include "MathGeoLib\include\Algorithm\Random\LCG.h"

namespace MathUtils
{
	Vector3 RandomPointInSphere(math::LCG& randomGenerator);
	Vector3 RandomPointInDisk(math::LCG& randomGenerator);
	Vector3 ReflectedVector(const Vector3& inVector, const Vector3& normal);
}

#endif // !MATHUTILS_H
