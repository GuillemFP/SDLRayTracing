#include "Globals.h"

#if USE_CUDA
namespace math
{
	class LCG;
}

class Vector3;
class Ray;
class Entity;

struct RayTracingConstants
{
	float minDistance = 0.0f;
	float maxDistance = 1.0f;
};

namespace CudaHelper
{
	void CalculatePixelColorSamples(Vector3* dColors, const RayTracingConstants* constants, const Ray* rays, const Entity* entities, const size_t* numberOfEntities, math::LCG* randomGenerators);
}
#endif // USE_CUDA