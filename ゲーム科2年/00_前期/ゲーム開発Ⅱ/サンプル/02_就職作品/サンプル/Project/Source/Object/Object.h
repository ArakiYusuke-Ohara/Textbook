#pragma once
#include "DxLib.h"
#include "../Component/ComponentManager.h"
#include "../Component/Transform.h"
#include <vector>

class Component;

class Object
{
public:
	Object() = default;
	virtual ~Object() = default;

	void Update();

	template <class T>
	T* AddComponent();

	const Transform& GetTransform() const { return m_Transform; }

	void SetTransform(Transform transform) { m_Transform = transform; }

private:
	Transform m_Transform;
	std::vector<Component*> m_Components;
};

template<class T>
inline T* Object::AddComponent()
{
	T* component = new T;
	component->SetOwner(this);
	m_Components.push_back(component);
	ComponentManager::GetInstance()->Register<T>(component);

	return component;
}
