#include "ParseUtils.h"

#include "Config.h"
#include "Math.h"

namespace ParseUtils
{
	math::float3 parseVector(const ConfigArray& config)
	{
		math::float3 vector;

		vector.x = config.GetFloatRequired(0);
		vector.y = config.GetFloatRequired(1);
		vector.z = config.GetFloatRequired(2);

		return vector;
	}
}