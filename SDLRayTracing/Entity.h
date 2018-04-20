#ifndef ENTITY_H
#define ENTITY_H

namespace math
{
	class Ray;
}

enum class EntityType
{
	Sphere,
	Unknown
};

class Entity
{
public:
	Entity(EntityType type) : _type(type) {}
	~Entity() = default;

	virtual bool Hit(const math::Ray& ray) const = 0;
	EntityType GetType() const
	{
		return _type;
	}

private:
	EntityType _type = EntityType::Unknown;
};

#endif // !ENTITY_H