#include "Player.h"
#include "PlayerManager.h"
#include "PlayerParameter.h"
#include "../Input//Input.h"
#include "../MyMath/MyMath.h"
#include "../Bullet/BulletManager.h"
#include "../Bullet/BulletParameter.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"
#include "../Bullet/BulletBase.h"
#include "../Stage/StageParameter.h"
#include "../Block/Block.h"

// コンストラクタ
Player::Player()
{
}

// デストラクタ
Player::~Player()
{
	Fin();
}

// ステップ
void Player::Step()
{
	if (!m_Active) return;

	PlayerBase::Step();

	// 移動入力
	InputMove();

	// 移動量から向き設定
	SetDirectionForMove();

	// バレット入力
	InputBullet();
}

void Player::InputMove()
{
	// 硬直中は移動できない
	if (m_Stiffness > 0) return;

	m_Move = VGet(0.0f, 0.0f, 0.0f);

	if (Input::IsInputKey(KEY_UP))
	{
		m_Move.y = -m_MoveSpeed;
	}
	else if (Input::IsInputKey(KEY_DOWN))
	{
		m_Move.y = m_MoveSpeed;
	}
	else if (Input::IsInputKey(KEY_LEFT))
	{
		m_Move.x = -m_MoveSpeed;
	}
	else if (Input::IsInputKey(KEY_RIGHT))
	{
		m_Move.x = m_MoveSpeed;
	}

	// 移動ベクトルを移動速度の大きさにする
	m_Move = MyMath::VecNormalize(m_Move);
	m_Move = MyMath::VecScale(m_Move, m_MoveSpeed);

	// 移動
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);
}

void Player::InputBullet()
{
	// Zキーで発射
	if (Input::IsTriggerKey(KEY_Z))
	{
		PlayerBase::FireBullet();
	}
}
