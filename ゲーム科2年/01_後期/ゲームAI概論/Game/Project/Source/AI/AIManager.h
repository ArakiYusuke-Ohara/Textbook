#pragma once

#include "../Singleton/Singleton.h"
#include <vector>

class AIStrategyBase;

class AIManager : public Singleton<AIManager>
{
public:
	AIManager();
	~AIManager();

public:
	// テンプレートを使えば生成関数は簡単に作れる
	template <typename T>
	T* CreateAI() {
		T* strategy = new T;
		m_Strategies.push_back(strategy);
		return strategy;
	}

	void Step();
	void Draw();
	void Fin();

private:
	std::vector<AIStrategyBase*> m_Strategies;
};
