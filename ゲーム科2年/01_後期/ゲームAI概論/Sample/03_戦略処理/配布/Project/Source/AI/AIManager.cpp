#include "AIManager.h"
#include "AIStrategyBase.h"
#include "AIParameter.h"

AIManager::AIManager()
{
}

AIManager::~AIManager()
{
}

void AIManager::Draw()
{
	for (AIStrategyBase* strategy : m_Strategies)
	{
		strategy->Draw();
	}
}

void AIManager::Fin()
{
	for (AIStrategyBase* strategy : m_Strategies)
	{
		delete strategy;
	}

	m_Strategies.clear();
	m_Strategies.shrink_to_fit();
}

