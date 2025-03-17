#pragma once
#include "AIStrategyBase.h"

class AIPlayCPU : public AIStrategyBase
{
public:
	AIPlayCPU();
	~AIPlayCPU() {}

public:
	int ThinkStrategy() override;
	void Draw() override;

public:
	void SetAwayDistance(float dist) { m_AwayDistance = dist; }

private:
	float m_AwayDistance;
};
