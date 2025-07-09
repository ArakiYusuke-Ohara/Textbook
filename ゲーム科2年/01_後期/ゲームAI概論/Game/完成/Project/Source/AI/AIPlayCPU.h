#pragma once
#include "AIStrategyBase.h"

class PlayerBase;
class Item;

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

	PlayerBase* FindNearestPlayer();
	Item* FindNearestItem();

private:
	float m_AwayDistance;
};
