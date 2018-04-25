#ifndef SCATTERINFO_H
#define SCATTERINFO_H

#include "MathGeoLib\include\Geometry\Ray.h"
#include "MathGeoLib\include\Math\float3.h"

struct ScatterInfo
{
	bool scatters = false;
	math::float3 attenuation;
	math::Ray scatteredRay;
};

#endif // !SCATTERINFO_H