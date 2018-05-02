#ifndef SCATTERINFO_H
#define SCATTERINFO_H

#include "MathGeoLib\include\Geometry\Ray.h"
#include "MathGeoLib\include\Math\float3.h"

struct ScatterInfo
{
	bool refracts = false;
	bool reflects = false;
	float refractionCoeff = 1.0f;
	float reflectionCoeff = 1.0f;
	math::float3 attenuation;
	math::Ray reflectedRay;
	math::Ray refractedRay;
};

#endif // !SCATTERINFO_H