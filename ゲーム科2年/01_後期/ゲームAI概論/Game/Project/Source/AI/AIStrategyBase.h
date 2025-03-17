#pragma once
#include "DxLib.h"

class PlayerBase;

class AIStrategyBase
{
public:
	AIStrategyBase();
	virtual ~AIStrategyBase() {}

public:
	virtual int ThinkStrategy() = 0;
	virtual void Draw();

	void SetOwner(PlayerBase* owner) { m_Owner = owner; }
	void SetTarget(VECTOR target) { m_Target = target; }

protected:
	const PlayerBase* m_Owner;
	VECTOR m_Target;
};
