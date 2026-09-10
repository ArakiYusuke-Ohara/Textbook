#pragma once
#include <vector>
#include "../Component/ComponentManager.h"

class Component;

class Object
{
public:
	Object() = default;
	virtual ~Object() = default;

	template <class T>
	T* AddComponent();

private:
	std::vector<Component*> m_Components;
};

template<class T>
inline T* Object::AddComponent()
{
	T* component = new T;
	m_Components.push_back(component);
	ComponentManager::GetInstance()->Register<ModelRenderer>(component);

	return component;
}
