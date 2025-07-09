#pragma once
#include "AIStrategyBase.h"

class AIRandomCPU : public AIStrategyBase
{
public:
	AIRandomCPU();
	~AIRandomCPU() {}

public:
	int ThinkStrategy() override;
	void Draw() override;
};
