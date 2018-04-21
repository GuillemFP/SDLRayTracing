#ifndef HITINFO_H
#define HITINFO_H

#include "MathGeoLib\include\Math\float3.h"

struct HitInfo
{
	bool isHit = false;
	float distance = 0.0f;
	math::float3 point;
	math::float3 normal;
};

#endif // !HITINFO_H