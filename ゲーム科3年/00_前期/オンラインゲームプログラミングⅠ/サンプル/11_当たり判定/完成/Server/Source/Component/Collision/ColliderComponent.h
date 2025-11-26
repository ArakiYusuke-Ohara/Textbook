#pragma once
#include "../ComponentBase.h"

enum class ColliderType
{
	AABB,
	SPHERE,
};

class ColliderComponent : public ComponentBase
{
protected:
	ColliderComponent() = default;
	virtual ~ColliderComponent() = default;

public:
	virtual bool IsCollide(const ColliderComponent& other) const = 0;

protected:
	ColliderType m_Type;
};
