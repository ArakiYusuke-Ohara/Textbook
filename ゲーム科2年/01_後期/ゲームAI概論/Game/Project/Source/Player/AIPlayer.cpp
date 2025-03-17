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

	if (m_AIStrategy)
	{
		// 一定時間ごとに戦略を考える
		if (m_StrategyTimer <= 0)
		{
			// ターゲットを設定
			Player* player1 = PlayerManager::GetInstance()->GetPlayer(0);
			VECTOR player1Pos = player1->GetPos();
			m_AIStrategy->SetTarget(player1Pos);

			// 戦略を決定して取得
			m_NowStrategy = m_AIStrategy->ThinkStrategy();

			// タイマーリセット
			m_StrategyTimer = PLYAER_CHANGE_STRATEGY_TIME;
		}

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
	m_Move = MyMath::VecScale(m_Move, PLAYER_SPEED);

	// 移動
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);

}

void AIPlayer::Away()
{
	// 1Pから離れる
	Player* player1 = PlayerManager::GetInstance()->GetPlayer(0);
	VECTOR player1Pos = player1->GetPos();
	m_Move = MyMath::VecCreate(m_Pos, player1Pos);
	m_Move = MyMath::VecNormalize(m_Move);
	m_Move = MyMath::VecScale(m_Move, -PLAYER_SPEED);

	// 移動
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);
}

void AIPlayer::Attack()
{
	PlayerBase::FireBullet();
}
