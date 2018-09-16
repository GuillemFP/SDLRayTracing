#include "PerlinNoise.h"

#include "MathGeoLib\include\Algorithm\Random\LCG.h"
#include "Math.h"

namespace
{
	const int kLength = 256;
	const int kInterpolationSteps = 2;

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

	inline int ApplyMask(const int n)
	{
		return n & 255;
	}

	inline float InterpolationFactor(int i, float u)
	{
		return (i*u + (1 - i)*(1 - u));
	}

	inline float Interpolation(float c[kInterpolationSteps][kInterpolationSteps][kInterpolationSteps], float u, float v, float w)
	{
		float sum = 0;

		for (int i = 0; i < kInterpolationSteps; ++i)
			for (int j = 0; j < kInterpolationSteps; ++j)
				for (int k = 0; k < kInterpolationSteps; ++k)
					sum += InterpolationFactor(i, u)*InterpolationFactor(j, v)*InterpolationFactor(k, w)*c[i][j][k];

		return sum;
	}
}

PerlinNoise::PerlinNoise(math::LCG& rng)
{
	_ranfloat = InitPerlin(rng);
	_permutation_x = InitPermutation(rng);
	_permutation_y = InitPermutation(rng);
	_permutation_z = InitPermutation(rng);
}

PerlinNoise::~PerlinNoise()
{
}

float PerlinNoise::Noise(const Vector3& p) const
{
	float u = GetDecimalPart(p.e[0]);
	float v = GetDecimalPart(p.e[1]);
	float w = GetDecimalPart(p.e[2]);
	int i = floor(p.e[0]);
	int j = floor(p.e[1]);
	int k = floor(p.e[2]);
	float c[kInterpolationSteps][kInterpolationSteps][kInterpolationSteps];
	for (int di = 0; di < kInterpolationSteps; ++di)
		for (int dj = 0; dj < kInterpolationSteps; ++dj)
			for (int dk = 0; dk < kInterpolationSteps; ++dk)
				c[di][dj][dk] = _ranfloat[_permutation_x[ApplyMask(i + di)] ^ _permutation_y[ApplyMask(j + dj)] ^ _permutation_z[ApplyMask(k + dk)]];

	return Interpolation(c, u, v, w);
}