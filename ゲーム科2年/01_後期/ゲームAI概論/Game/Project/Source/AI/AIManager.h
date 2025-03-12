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
	AIStrategyBase* CreateAI(int type);

	void Step();
	void Draw();
	void Fin();

private:
	std::vector<AIStrategyBase*> m_Strategies;
};
