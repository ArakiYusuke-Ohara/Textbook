#pragma once
#include "ColliderComponent.h"
#include "DxLib.h"

class AABB : public ColliderComponent
{
public:
	AABB();
	~AABB() = default;

	void SetCenter(const VECTOR& center) { m_Center = center; }
	void SetSize(const VECTOR& size) { m_Size = size; }

	bool IsCollide(const ColliderComponent& other) const override;
	bool IsCollideAABB(const AABB& other) const;

private:
	VECTOR m_Center;
	VECTOR m_Size;
};
