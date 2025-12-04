#pragma once
#include <vector>
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

	const VECTOR& GetPosition() const { return m_Transform.GetPosition(); }

	void Move(const VECTOR& vec);

	// コンポーネント追加
	template <class T>
	T* AddComponent()
	{
		UniquePtr<T>component = MakeUnique<T>();
		component->SetOwner(this);          
		T* rawPtr = component.get();
		m_Components.emplace_back(std::move(component));  

		return rawPtr;
	}

private:
	// トランスフォームは必ず持つ
	Transform m_Transform;

	// 他に必要な機能はコンポーネントとして後付けしていく
	std::vector<SharedPtr<ComponentBase>> m_Components;
};
