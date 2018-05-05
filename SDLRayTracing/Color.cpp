#include "Color.h"

#include "Vector3.h"

Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
{
}

Color::Color(const Vector3& color) : r(color.x()), g(color.y()), b(color.z()), a(1.0f)
{

}

void Color::SetColor(float r, float g, float b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}
