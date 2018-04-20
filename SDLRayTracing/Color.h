#ifndef COLOR_H
#define COLOR_H

namespace math
{
	class float3;
}

struct Color
{
public:
	Color() = default;
	Color(float r, float g, float b, float a = 1.0f);
	Color(const math::float3& color);
	~Color() = default;

	void SetColor(float r, float g, float b);

public:
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
	float a = 1.0f;
};

#endif // !COLOR_H