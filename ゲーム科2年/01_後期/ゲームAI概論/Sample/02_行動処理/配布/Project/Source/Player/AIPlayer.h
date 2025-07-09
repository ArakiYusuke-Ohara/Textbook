#pragma once
#include "Player.h"

class AIPlayer : public Player
{
public:
	AIPlayer();

public:
	void Step() override;

	// AIが選択した戦略に対する行動
	void ChaseTarget();	// ターゲットを追いかける
	void Away();		// ターゲットから離れる
	void Attack();		// 攻撃する

	void SetAIStrategy(AIStrategyBase* strategy) { m_AIStrategy = strategy; }
	void SetDirectionForTarget();

private:
	VECTOR GetTargetChaseVec(VECTOR targetPos);

protected:
	int m_StrategyTimer;
	int m_NowStrategy;
	int m_PlayerChaseInterval;

	// 遂行中の戦略
	AIStrategyBase* m_AIStrategy;
};
