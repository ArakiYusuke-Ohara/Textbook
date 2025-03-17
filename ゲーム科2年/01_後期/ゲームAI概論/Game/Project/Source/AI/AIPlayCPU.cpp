#include "AIPlayCPU.h"
#include "AIParameter.h"
#include "../Player/Player.h"
#include "../MyMath/MyMath.h"

AIPlayCPU::AIPlayCPU()
{
	m_AwayDistance = 0.0f;
}

// この関数にCPUのとる行動を決定する処理を書く
int AIPlayCPU::ThinkStrategy()
{
	// オーナーが無い場合は決定できない
	if (!m_Owner) return CPU_STRATEGY_NONE;

	// バレットインターバル中は離れる
	if (m_Owner->IsBulletInterval())
	{
		return CPU_STRATEGY_AWAY;
	}

	// ターゲットまでの距離を計算
	VECTOR ownerPos = m_Owner->GetPos();
	VECTOR targetVec = MyMath::VecCreate(ownerPos, m_Target);
	float dist = MyMath::VecLong(targetVec);
	// 一定距離近づいたら攻撃
	if (dist <= m_AwayDistance)
	{
		return CPU_STRATEGY_ATTACK;
	}

	// 何もすることがなければ追跡
	return CPU_STRATEGY_CHASE;
}

void AIPlayCPU::Draw()
{
}
