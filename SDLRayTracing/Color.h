#ifndef COLOR_H
#define COLOR_H

struct Color
{
public:
	Color() = default;
	Color(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) {}
	~Color() = default;

	void SetColor(float r, float g, float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}

public:
	float r = 0.0f;
	float g = 0.0f;
	float b = 0.0f;
	float a = 1.0f;
};

#endif // !COLOR_H