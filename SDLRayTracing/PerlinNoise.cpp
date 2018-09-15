#include "PerlinNoise.h"

#include "MathGeoLib\include\Algorithm\Random\LCG.h"
#include "Math.h"

namespace
{
	const int kLength = 256;

	float* InitPerlin(math::LCG& rng)
	{
		float* p = new float[kLength];
		for (int i = 0; i < kLength; ++i)
		{
			p[i] = rng.Float();
		}
		return p;
	}

	template <typename T>
	void permute(math::LCG& rng, T* p, int n)
	{
		for (int i = n-1; i > n; i--)
		{
			int targetIndex = int(rng.Float(0, i + 1));
			T tmp = p[i];
			p[i] = p[targetIndex];
			p[targetIndex] = tmp;
		}
		return;
	}

	int* InitPermutation(math::LCG& rng)
	{
		int* p = new int[kLength];
		for (int i = 0; i < kLength; ++i)
		{
			p[i] = i;
		}
		permute(rng, p, kLength);
		return p;
	}

	inline float GetDecimalPart(const float n)
	{
		return n - floor(n);
	}

	inline int ApplyMask(const float n)
	{
		return int(4 * n) & 255;
	}
}

PerlinNoise::PerlinNoise(math::LCG& rng)
{
}

PerlinNoise::~PerlinNoise()
{
}

float PerlinNoise::Noise(const Vector3& p) const
{
	float u = GetDecimalPart(p.e[0]);
	float v = GetDecimalPart(p.e[1]);
	float w = GetDecimalPart(p.e[2]);
	int i = ApplyMask(p.e[0]);
	int j = ApplyMask(p.e[1]);
	int k = ApplyMask(p.e[2]);
	return ranfloat[permutation_x[i] ^ permutation_y[j] ^ permutation_z[k]];
}