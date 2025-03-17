#pragma once
#include "Player.h"

class AIPlayer : public Player
{
public:
	AIPlayer();

public:
	void Step() override;

	void Chase();
	void Away();
	void Attack();

	void SetAIStrategy(AIStrategyBase* strategy) { m_AIStrategy = strategy; }

protected:
	int m_StrategyTimer;
	int m_NowStrategy;
	AIStrategyBase* m_AIStrategy;
};