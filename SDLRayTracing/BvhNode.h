#ifndef BVHNODE_H
#define BVHNODE_H

#include "Entity.h"
#include "AABB.h"

class BvhNode
{
public:
	BvhNode(const Entity** entities, const size_t entitiesSize);
	~BvhNode();

	bool Hit(const Ray& ray, float minDistance, float maxDistance, HitInfo& hitInfo) const;

	const AABB& GetBoundingBox() const { return _boundingBox; }

private:
	const Entity* _entity = nullptr;

	BvhNode* _firstChild = nullptr;
	BvhNode* _secondChild = nullptr;
	AABB _boundingBox;
};

#endif // !BVHNODE_H