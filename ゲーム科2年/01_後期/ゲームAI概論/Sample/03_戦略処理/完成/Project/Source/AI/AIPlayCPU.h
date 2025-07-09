#pragma once
#include "AIStrategyBase.h"

class PlayerBase;

class AIPlayCPU : public AIStrategyBase
{
public:
	AIPlayCPU();
	~AIPlayCPU() {}

public:
	int ThinkStrategy() override;
	void Draw() override;

public:
	void SetAttackDistance(float dist) { m_AttackDistance = dist; }

	PlayerBase* FindNearestPlayer();

private:
	float m_AttackDistance;
};

