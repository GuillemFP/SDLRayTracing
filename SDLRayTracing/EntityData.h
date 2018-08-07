#ifndef ENTITYDATA_H
#define ENTITYDATA_H

#include "MaterialData.h"
#include "ShapeData.h"

struct EntityData
{
	ShapeData shapeData;
	MaterialData materialData;
};

#endif // !ENTITYDATA_H