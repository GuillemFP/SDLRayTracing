#ifndef HITINFO_H
#define HITINFO_H

#include "Vector3.h"

class Material;

struct HitInfo
{
	bool isHit = false;
	float distance = 0.0f;
	Vector3 point;
	Vector3 normal;
	const Material* material;
};

#endif // !HITINFO_H