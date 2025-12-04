#include "GameObject.h"

GameObject::GameObject()
{
	m_Transform = {};
	m_Components = {};
}

void GameObject::Move(const VECTOR& vec)
{
	VECTOR pos = m_Transform.GetPosition();
	pos = VAdd(pos, vec);
	m_Transform.SetPos(pos);
}
