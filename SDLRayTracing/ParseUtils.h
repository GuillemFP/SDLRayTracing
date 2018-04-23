#ifndef PARSEUTILS_H
#define PARSEUTILS_H

#include "MathGeoLib\include\Math\float3.h"

class Config;
class ConfigArray;

namespace ParseUtils
{
	math::float3 parseVector(const ConfigArray& config);
}

#endif // !PARSEUTILS_H