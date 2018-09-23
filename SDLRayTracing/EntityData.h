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
};

#endif // !ENTITYDATA_H