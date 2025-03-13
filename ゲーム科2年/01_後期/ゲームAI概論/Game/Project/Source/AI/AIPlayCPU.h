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
};
