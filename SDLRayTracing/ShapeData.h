#ifndef SHAPEDATA_H
#define SHAPEDATA_H

#include "Shape.h"

struct ShapeData
{
	Shape::Type type;
	float radius = 1.0f;
};

#endif // !SHAPEDATA_H