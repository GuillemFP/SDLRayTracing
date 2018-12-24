#ifndef PERLINNOISE_H
#define PERLINNOISE_H

namespace math
{
	class LCG;
}

class Vector3;

class PerlinNoise
{
public:
	PerlinNoise(math::LCG& rng);
	~PerlinNoise();

	float Noise(const Vector3& p) const;
	float Turbulence(const Vector3& p, const int depth = 1) const;

private:
	Vector3* _ranvec = nullptr;
	int* _permutation_x = nullptr;
	int* _permutation_y = nullptr;
	int* _permutation_z = nullptr;
};

#endif // !PERLINNOISE_H