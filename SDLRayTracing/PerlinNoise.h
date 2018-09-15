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
	float* ranfloat = nullptr;
	int* permutation_x = nullptr;
	int* permutation_y = nullptr;
	int* permutation_z = nullptr;
};

#endif // !PERLINNOISE_H