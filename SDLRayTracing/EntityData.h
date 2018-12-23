#ifndef ENTITYDATA_H
#define ENTITYDATA_H

#include "MaterialData.h"
#include "ShapeData.h"
#include "Vector3.h"

struct EntityData
{
	ShapeData shapeData;
	MaterialData materialData;
	Vector3 position;
	Vector3 rotation;
	Vector3 scale = Vector3::one;
	Vector3 speed;
	bool isSolid = true;
	float density = 1.0f;
};

#endif // !ENTITYDATA_H