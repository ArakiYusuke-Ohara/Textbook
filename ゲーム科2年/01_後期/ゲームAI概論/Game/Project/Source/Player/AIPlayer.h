#pragma once
#include "Player.h"

class AIPlayer : public Player
{
public:
	AIPlayer();

public:
	void Step() override;

	void ChaseTarget();
	void Away();
	void Attack();

	void SetAIStrategy(AIStrategyBase* strategy) { m_AIStrategy = strategy; }
	void SetDirectionForTarget();

private:
	VECTOR GetTargetChaseVec(VECTOR targetPos);

protected:
	int m_StrategyTimer;
	int m_NowStrategy;
	int m_PlayerChaseInterval;
	AIStrategyBase* m_AIStrategy;
};