#include "CudaHelper.cuh"

#if USE_CUDA
#include "Math.h"
#include "Ray.h"
#include "Vector3.h"
#include <cuda_runtime.h>
#include <cuda.h>
#include <curand_kernel.h>
#include "device_launch_parameters.h"

int main()
{
	return 0;
}

namespace CudaHelper
{
	void CalculatePixelColorSamples(Vector3* dColors, const RayTracingConstants* constants, const Ray* rays, const Entity* entities, const size_t* numberOfEntities, math::LCG* randomGenerators)
	{
		CalculatePixelColorSamples<<<1,1>>>(_dColorSamples, _dConstants, _dRays, _dEntities, _dEntityNumber, _dRandomGenerators);
	}

	CUDA_KERNEL void CalculatePixelColorSamples(Vector3* dColors, const RayTracingConstants* constants, const Ray* rays, const Entity* entities, const size_t* numberOfEntities, math::LCG* randomGenerators)
	{
		int blockIndex = blockIdx.x;

		Vector3& colorResult = dColors[blockIndex];
		const Ray& ray = rays[blockIndex];
		math::LCG& randomGenerator = randomGenerators[blockIndex];
	}
}
#endif // USE_CUDA