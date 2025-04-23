#include "AIPlayer.h"
#include "PlayerManager.h"
#include "PlayerParameter.h"
#include "../AI/AIStrategyBase.h"
#include "../AI/AIParameter.h"
#include "../MyMath/MyMath.h"

#define PLYAER_CHANGE_STRATEGY_TIME 180

AIPlayer::AIPlayer()
{
	m_StrategyTimer = 0;
	m_NowStrategy = 0;
	m_AIStrategy = nullptr;
}

void AIPlayer::Step()
{
	PlayerBase::Step();

	// 硬直中は何もしない
	if (m_Stiffness > 0) return;

	if (m_AIStrategy)
	{
		// ターゲットを設定
		Player* player1 = PlayerManager::GetInstance()->GetPlayer(0);
		VECTOR player1Pos = player1->GetPos();
		m_AIStrategy->SetTarget(player1Pos);

		// 戦略を決定して取得
		m_NowStrategy = m_AIStrategy->ThinkStrategy();

		// タイマーリセット
		m_StrategyTimer = PLYAER_CHANGE_STRATEGY_TIME;

		// 戦略によって移動処理が変わる
		switch (m_NowStrategy)
		{
			case CPU_STRATEGY_CHASE:	Chase();	break;
			case CPU_STRATEGY_AWAY:		Away();		break;
			case CPU_STRATEGY_ATTACK:	Attack();		break;
		}

		m_StrategyTimer--;
	}
}

void AIPlayer::Chase()
{
	// 1Pを追いかける
	Player* player1 = PlayerManager::GetInstance()->GetPlayer(0);
	VECTOR player1Pos = player1->GetPos();
	m_Move = MyMath::VecCreate(m_Pos, player1Pos);
	m_Move = MyMath::VecNormalize(m_Move);
	m_Move = MyMath::VecScale(m_Move, m_MoveSpeed);

	// 移動
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);

	// 移動量から向きを設定
	SetDirectionForMove();
}

void AIPlayer::Away()
{
	// 1Pから離れる
	Player* player1 = PlayerManager::GetInstance()->GetPlayer(0);
	VECTOR player1Pos = player1->GetPos();
	m_Move = MyMath::VecCreate(player1Pos, m_Pos);
	m_Move = MyMath::VecNormalize(m_Move);
	m_Move = MyMath::VecScale(m_Move, m_MoveSpeed);

	// 移動
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);

	// 移動量から向きを設定
	SetDirectionForMove();
}

void AIPlayer::Attack()
{
	// 1Pの方を向く
	SetDirectionForTarget();
	// 弾発射
	PlayerBase::FireBullet();
}

void AIPlayer::SetDirectionForTarget()
{
	// 1Pをターゲットとして向きを決定する
	Player* player1 = PlayerManager::GetInstance()->GetPlayer(0);

	// 1Pまでのベクトル
	VECTOR targetVec = MyMath::VecCreate(m_Pos, player1->GetPos());

	// X成分の方が長ければ横を向く
	if (MyMath::Absolute(targetVec.x) >= MyMath::Absolute(targetVec.y))
	{
		// プレイヤーが左にいれば左を向く
		if (targetVec.x < 0.0f)
		{
			m_Direction = PLAYER_DIRECTION_LEFT;
		}
		else
		{
			m_Direction = PLAYER_DIRECTION_RIGHT;
		}
	}
	else
	{
		// プレイヤーが上にいれば上を向く
		if (targetVec.y < 0.0f)
		{
			m_Direction = PLAYER_DIRECTION_UP;
		}
		else
		{
			m_Direction = PLAYER_DIRECTION_DOWN;
		}
	}
}
