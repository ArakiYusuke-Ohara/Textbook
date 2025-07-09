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

	VECTOR GetTarget() const { return m_Target; }

protected:
	const PlayerBase* m_Owner;
	VECTOR m_Target;
};
