#pragma once
#include "DxLib.h"

class Player;

class AIStrategyBase
{
public:
	AIStrategyBase();
	virtual ~AIStrategyBase() {}

public:
	virtual int ThinkStrategy() = 0;
	virtual void Draw();

	void SetOwner(Player* owner) { m_Owner = owner; }
	void SetTarget(VECTOR target) { m_Target = target; }

protected:
	Player* m_Owner;
	VECTOR m_Target;
};
