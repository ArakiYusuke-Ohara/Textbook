#include "AABB.h"
#include <cmath>

AABB::AABB()
{
	m_Type = ColliderType::AABB;
	m_Center = {};
	m_Size = {};
}

bool AABB::IsCollide(const ColliderComponent& other) const
{
	return false;
}

bool AABB::IsCollideAABB(const AABB& other) const
{

	return false;
}

