#include "AIPlayCPU.h"
#include "AIParameter.h"
#include "../Player/Player.h"
#include "../Player/PlayerManager.h"
#include "../MyMath/MyMath.h"

AIPlayCPU::AIPlayCPU()
{
	m_AttackDistance = 0.0f;
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
	if (dist <= m_AttackDistance)
	{
		return CPU_STRATEGY_ATTACK;
	}

	// ここまでで何もすることがなければ
	// 最も近いプレイヤーをターゲットとして追跡
	PlayerBase* player = FindNearestPlayer();
	if (player)
	{
		m_Target = player->GetPos();
	}

	return CPU_STRATEGY_CHASE_TARGET;
}

void AIPlayCPU::Draw()
{
}

/// <summary>
/// 最も近いプレイヤーを探して返す
/// </summary>
/// <returns>最も近いプレイヤー</returns>
PlayerBase* AIPlayCPU::FindNearestPlayer()
{
	Player* result = nullptr;
	float min = FLT_MAX;
	auto players = PlayerManager::GetInstance()->GetPlayers();

	for (Player* player : players)
	{
		// 自分自身は無視
		if (player == m_Owner) continue;
		// 死んでるプレイヤーは無視
		if (!player->IsActive()) continue;

		// 他プレイヤーまでの距離を計算
		float dist = MyMath::GetDistance(m_Owner->GetPos(), player->GetPos());
		// より近いプレイヤーだったら覚えておく
		if (dist < min)
		{
			result = player;
			min = dist;
		}
	}

	return result;
}
