#ifndef HITINFO_H
#define HITINFO_H

#include "Vector3.h"

class Entity;

struct HitInfo
{
	bool isHit = false;
	float distance = 0.0f;
	Vector3 point;
	Vector3 normal;
	const Entity* entity;
	float u = 0;
	float v = 0;
};

#endif // !HITINFO_H