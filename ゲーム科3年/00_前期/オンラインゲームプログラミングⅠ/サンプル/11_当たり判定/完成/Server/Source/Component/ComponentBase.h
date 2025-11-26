#pragma once
#include "../Object/GameObject.h"

class ComponentBase
{
public:
	ComponentBase(const GameObject* owner);
	virtual ~ComponentBase() = default;

private:
	const GameObject* m_Owner;
};
