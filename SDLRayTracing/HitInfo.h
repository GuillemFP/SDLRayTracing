#ifndef HITINFO_H
#define HITINFO_H

#include "MathGeoLib\include\Math\float3.h"

struct HitInfo
{
	float t = -1.0f;
	math::float3 point;
	math::float3 normal;
};

#endif // !HITINFO_H