#ifndef SCATTERINFO_H
#define SCATTERINFO_H

#include "Ray.h"
#include "Vector3.h"

struct ScatterInfo
{
	bool refracts = false;
	bool reflects = false;
	float refractionCoeff = 1.0f;
	float reflectionCoeff = 1.0f;
	Vector3 attenuation;
	Ray reflectedRay;
	Ray refractedRay;
};

#endif // !SCATTERINFO_H