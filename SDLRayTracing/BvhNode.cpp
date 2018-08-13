#include "BvhNode.h"

#include "HitInfo.h"
#include "Ray.h"
#include <algorithm>

BvhNode::BvhNode(Entity* entities, const size_t entitiesSize)
{
	std::sort(entities, entities+entitiesSize, [](const Entity& e1, const Entity& e2)
	{
		return e1.CreateBoundingBox().GetMin().e[0] < e2.CreateBoundingBox().GetMin().e[0];
	});

	if (entitiesSize == 1)
	{
		_entity = entities[0];
		_boundingBox = _entity.CreateBoundingBox();
	}
	else
	{
		const size_t firstChildSize = entitiesSize / 2;
		const size_t secondChildSize = entitiesSize - firstChildSize;

		_firstChild = new BvhNode(entities, firstChildSize);
		_secondChild = new BvhNode(entities + firstChildSize, secondChildSize);
		_boundingBox = AABB::SurroundingBox(_firstChild->GetBoundingBox(), _secondChild->GetBoundingBox());
	}
}

BvhNode::~BvhNode()
{
	RELEASE(_firstChild);
	RELEASE(_secondChild);
}

bool BvhNode::Hit(const Ray& ray, const float minDistance, const float maxDistance, HitInfo& hitInfo) const
{
	if (_boundingBox.Hit(ray, minDistance, maxDistance))
	{
		if (!_firstChild && !_secondChild)
		{
			return _entity.Hit(ray, minDistance, maxDistance, hitInfo);
		}
		else
		{
			HitInfo firstChildInfo;
			HitInfo secondChildInfo;
			bool firstHit = _firstChild->Hit(ray, minDistance, maxDistance, firstChildInfo);
			bool secondHit = _secondChild->Hit(ray, minDistance, maxDistance, secondChildInfo);
			if (firstHit && secondHit)
			{
				if (firstChildInfo.distance < secondChildInfo.distance)
					hitInfo = firstChildInfo;
				else
					hitInfo = secondChildInfo;
				return true;
			}
			else if (firstHit)
			{
				hitInfo = firstChildInfo;
				return true;
			}
			else if (secondHit)
			{
				hitInfo = secondChildInfo;
				return true;
			}
			else
				return false;
		}
	}

	return false;
}
