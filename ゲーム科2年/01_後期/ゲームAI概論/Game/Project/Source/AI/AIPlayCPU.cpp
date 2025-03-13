#include "AIPlayCPU.h"
#include "AIParameter.h"
#include "../Player/Player.h"
#include "../MyMath/MyMath.h"

AIPlayCPU::AIPlayCPU()
{
	m_Target = VGet(0.0f, 0.0f, 0.0f);
}

// この関数にCPUのとる行動を決定する処理を書く
int AIPlayCPU::ThinkStrategy()
{
	// オーナーが無い場合は決定できない
	if (!m_Owner) return CPU_STRATEGY_NONE;

	// ターゲットまでの距離を計算
	VECTOR ownerPos = m_Owner->GetPos();
	VECTOR targetVec = MyMath::VecCreate(ownerPos, m_Target);
	float dist = MyMath::VecLong(targetVec);

	// 距離が30以下であれば離れる
	if (dist <= 30.0f)
	{
		return CPU_STRATEGY_AWAY;
	}

	// そうでなければ追いかける
	return CPU_STRATEGY_CHASE;
}

void AIPlayCPU::Draw()
{
}
