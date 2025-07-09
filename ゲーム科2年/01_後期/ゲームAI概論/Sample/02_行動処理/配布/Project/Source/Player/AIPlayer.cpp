#include "AIPlayer.h"
#include "PlayerManager.h"
#include "PlayerParameter.h"
#include "../MyMath/MyMath.h"

#define PLYAER_CHANGE_STRATEGY_TIME 180
#define PLAYER_CHASE_INTERVAL 30

AIPlayer::AIPlayer()
{
	m_StrategyTimer = 0;
	m_NowStrategy = 0;
	m_PlayerChaseInterval = 0;
	m_AIStrategy = nullptr;
}

void AIPlayer::Step()
{
	if (!m_Active) return;

	PlayerBase::Step();

	// 硬直中は何もしない
	if (m_Stiffness > 0) return;

	if (m_AIStrategy)
	{
		// 戦略を決定して取得


		// タイマーリセット
		m_StrategyTimer = PLYAER_CHANGE_STRATEGY_TIME;

		// 戦略によって移動処理が変わる


		m_StrategyTimer--;
	}
}

/// <summary>
/// 自分に最も近いプレイヤーを追いかける
/// </summary>
void AIPlayer::ChaseTarget()
{
	// 一定時間ごとに方向を決める
	if (m_PlayerChaseInterval <= 0)
	{
		// ターゲットに向かって移動する


		// インターバル設定
		m_PlayerChaseInterval = PLAYER_CHASE_INTERVAL;
	}
	else
	{
		m_PlayerChaseInterval--;
	}

	// 移動
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);

	// 移動量から向きを設定
	SetDirectionForMove();
}

void AIPlayer::Away()
{
	// ターゲット座標を取得


	// 離れる場合は向きを反転するだけ
	m_Move = MyMath::VecScale(m_Move, -1.0f);

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
	// ターゲット座標を取得


	// ターゲットまでのベクトル
	VECTOR targetVec = {};

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

/// <summary>
/// ターゲットに向かう移動ベクトルを取得する
/// ゲームの仕様上、縦横方向にしか移動できないようにするため
/// </summary>
/// <param name="targetPos">ターゲットの座標</param>
/// <returns>縦横移動ベクトル</returns>
VECTOR AIPlayer::GetTargetChaseVec(VECTOR targetPos)
{
	VECTOR result = {};
	result = MyMath::VecCreate(m_Pos, targetPos);
	result = MyMath::VecNormalize(result);


	float absMoveX = MyMath::Absolute(result.x);
	float absMoveY = MyMath::Absolute(result.y);
	// X, Yで長い方を採用
	if (absMoveX > absMoveY)
	{
		result.y = 0.0f;
	}
	else
	{
		result.x = 0.0f;
	}

	result = MyMath::VecNormalize(result);
	result = MyMath::VecScale(result, m_MoveSpeed);

	return result;
}
