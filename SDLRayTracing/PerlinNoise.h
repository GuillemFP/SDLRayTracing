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

private:
	float* _ranfloat = nullptr;
	int* _permutation_x = nullptr;
	int* _permutation_y = nullptr;
	int* _permutation_z = nullptr;
};

#endif // !PERLINNOISE_H