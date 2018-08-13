#ifndef BVHNODE_H
#define BVHNODE_H

#include "Entity.h"
#include "AABB.h"

class BvhNode
{
public:
	BvhNode(Entity* entities, const size_t entitiesSize);
	~BvhNode();

	bool Hit(const Ray& ray, const float minDistance, const float maxDistance, HitInfo& hitInfo) const;

	const AABB& GetBoundingBox() const { return _boundingBox; }

private:
	Entity _entity;

	BvhNode* _firstChild = nullptr;
	BvhNode* _secondChild = nullptr;
	AABB _boundingBox;
};

#endif // !BVHNODE_H