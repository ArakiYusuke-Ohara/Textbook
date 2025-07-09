#pragma once
#include "DxLib.h"

class PlayerBase;

class AIStrategyBase
{
public:
	AIStrategyBase();
	virtual ~AIStrategyBase() {}

public:
	// 戦略を考えて決定する関数
	virtual int ThinkStrategy() = 0;
	// デバッグ用に何か描画するかも
	virtual void Draw();

	void SetOwner(PlayerBase* owner) { m_Owner = owner; }

	VECTOR GetTarget() const { return m_Target; }

protected:
	// このAIによって動くプレイヤー
	const PlayerBase* m_Owner;
	// 行動のターゲットとなる座標
	VECTOR m_Target;
};

