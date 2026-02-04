#pragma once

#include "../Singleton/Singleton.h"
#include "ObjectMoverBase.h"
#include "ObjectMoverParameter.h"
#include <vector>

class EaseInOut;

class ObjectMoverManager : public Singleton<ObjectMoverManager>
{
public:
	ObjectMoverManager();
	~ObjectMoverManager();

public:
	void Fin();


public:
	const EaseInOutParam* GetEaseInOutParam(int id);

public:
	std::vector<ObjectMoverBase*> m_Moveres;

public:
	// templateを使えば型指定の生成処理が作れる
	// ただしコンパイルの都合上、ヘッダーファイルに処理を書くことになる。
	template <typename T>
	T* CreateObjectMover()
	{
		for (ObjectMoverBase* mover : m_Moveres)
		{
			if (!mover->IsActive() && typeid(*mover) == typeid(T))
			{
				return static_cast<T*>(mover);
			}
		}

		T* mover = new T;
		m_Moveres.push_back(mover);

		return mover;
	}
};