#include "AIManager.h"
#include "AIStrategyBase.h"
#include "AIParameter.h"

AIManager::AIManager()
{
}

AIManager::~AIManager()
{
}

void AIManager::Step()
{
}

void AIManager::Draw()
{
}

void AIManager::Fin()
{
}

AIStrategyBase* AIManager::CreateAI(int type)
{
	switch (type)
	{
		case AI_STRATEGY_TYPE_A:
			return new AIStrategyBase;
			break;

		case AI_STRATEGY_TYPE_B:
			return new AIStrategyBase;
			break;

		case AI_STRATEGY_TYPE_C:
			return new AIStrategyBase;
			break;
	}
}
