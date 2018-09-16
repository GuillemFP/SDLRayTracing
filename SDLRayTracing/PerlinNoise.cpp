#include "PerlinNoise.h"

#include "MathGeoLib\include\Algorithm\Random\LCG.h"
#include "Math.h"

namespace
{
	const int kLength = 256;
	const int kInterpolationSteps = 2;

	Vector3* InitPerlin(math::LCG& rng)
	{
		Vector3* p = new Vector3[kLength];
		for (int i = 0; i < kLength; ++i)
		{
			p[i] = normalize(Vector3(rng.FloatIncl(-1.0f, 1.0f), rng.FloatIncl(-1.0f, 1.0f), rng.FloatIncl(-1.0f, 1.0f)));
		}
		return p;
	}

	template <typename T>
	void permute(math::LCG& rng, T* p, int n)
	{
		for (int i = n-1; i > n; i--)
		{
			int targetIndex = rng.Int(0, i);
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

	inline float GetDecimalPart(const float u)
	{
		return u - floor(u);
	}

	inline float HermitCubic(const float u)
	{
		return u*u*(3.0f - 2.0f*u);
	}

	inline int ApplyMask(const int n)
	{
		return n & 255;
	}

	inline float InterpolationFactor(int i, float u)
	{
		return (i*u + (1 - i)*(1 - u));
	}

	inline float Interpolation(Vector3 c[kInterpolationSteps][kInterpolationSteps][kInterpolationSteps], float u, float v, float w)
	{
		float uu = HermitCubic(u);
		float vv = HermitCubic(v);
		float ww = HermitCubic(w);
		float sum = 0;
		for (int i = 0; i < kInterpolationSteps; ++i)
			for (int j = 0; j < kInterpolationSteps; ++j)
				for (int k = 0; k < kInterpolationSteps; ++k)
				{
					Vector3 weight(u - i, v - j, w - k);
					sum += InterpolationFactor(i, uu)*InterpolationFactor(j, vv)*InterpolationFactor(k, ww)*dot(c[i][j][k], weight);
				}
		return sum;
	}
}

PerlinNoise::PerlinNoise(math::LCG& rng)
{
	_ranvec = InitPerlin(rng);
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
	Vector3 c[kInterpolationSteps][kInterpolationSteps][kInterpolationSteps];
	for (int di = 0; di < kInterpolationSteps; ++di)
		for (int dj = 0; dj < kInterpolationSteps; ++dj)
			for (int dk = 0; dk < kInterpolationSteps; ++dk)
				c[di][dj][dk] = _ranvec[_permutation_x[ApplyMask(i + di)] ^ _permutation_y[ApplyMask(j + dj)] ^ _permutation_z[ApplyMask(k + dk)]];

	return Interpolation(c, u, v, w);
}