#include "Object.h"

void Object::Update()
{
	for (Component* component : m_Components)
	{
		component->Update();
	}
}