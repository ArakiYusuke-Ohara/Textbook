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
	void SetDirectionForTarget();

private:
	void CalcPlayerChaseVec();

protected:
	int m_StrategyTimer;
	int m_NowStrategy;
	int m_PlayerChaseInterval;
	AIStrategyBase* m_AIStrategy;
};