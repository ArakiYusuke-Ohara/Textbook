#include "AIStrategyBase.h"

AIStrategyBase::AIStrategyBase()
{
	m_Owner = nullptr;
	m_Target = VGet(0.0f, 0.0f, 0.0f);
}


void AIStrategyBase::Draw()
{
}

