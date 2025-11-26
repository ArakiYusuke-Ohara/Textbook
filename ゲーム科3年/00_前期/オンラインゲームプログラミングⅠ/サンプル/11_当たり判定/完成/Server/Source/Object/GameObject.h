#pragma once
#include <list>
#include "../Memory/Memory.h"
#include "../Component/Transform/Transform.h"
#include "../Component/ComponentBase.h"

class GameObject
{
public:
	GameObject();
	~GameObject() = default;

	void SetPosition(const VECTOR& pos) { m_Transform.SetPos(pos); }
	void SetRotation(const VECTOR& rot) { m_Transform.SetRot(rot); }
	void SetScale(const VECTOR& scale) { m_Transform.SetScale(scale); }

	void AddComponent(SharedPtr<ComponentBase> component) { m_Components.push_back(std::move(component)); }

private:
	// トランスフォームは必ず持つ
	Transform m_Transform;

	// 他に必要な機能はコンポーネントとして後付けしていく
	std::list<SharedPtr<ComponentBase>> m_Components;
};
