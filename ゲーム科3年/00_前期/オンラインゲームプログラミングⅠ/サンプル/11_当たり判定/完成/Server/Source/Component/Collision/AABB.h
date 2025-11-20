#pragma once
#include "../ComponentBase.h"
#include "DxLib.h"

class AABB : public ComponentBase
{
public:
	AABB();
	~AABB() = default;

private:
	VECTOR m_Center;
	VECTOR m_Size;
};
