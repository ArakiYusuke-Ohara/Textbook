#pragma once

class GameObject;

class ComponentBase
{
public:
	ComponentBase();
	virtual ~ComponentBase() = default;

	void SetOwner(GameObject* owner) { m_Owner = owner; }
	GameObject* GetOwner()  { return m_Owner; }

protected:
	GameObject* m_Owner;
};
