#pragma once

class Object;

class Component
{
public:
	Component() = default;
	virtual ~Component() = default;

	virtual void Update();

	Object* GetOwner() const { return m_Owner; }

	void SetOwner(Object* owner) { m_Owner = owner; }


private:
	Object* m_Owner;
};