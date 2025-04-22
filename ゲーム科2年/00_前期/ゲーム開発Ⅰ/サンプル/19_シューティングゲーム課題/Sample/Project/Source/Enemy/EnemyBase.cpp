#include "EnemyBase.h"
#include "../MyMath/MyMath.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../Bullet/BulletBase.h"
#include "../Collision/CollisionSphere.h"
#include "../ObjectMover/ObjectMoverManager.h"
#include "../ObjectMover/ObjectMoverBase.h"
#include "../ObjectMover/EaseInOut.h"
#include "../MyEffekseer/EffekseerManager.h"

EnemyBase::EnemyBase()
{
	m_Active = false;
	m_Handle = 0;
	m_Hp = 0;
	m_Interval = 0;
	m_EncountDist = 0.0f;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_DrawPos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_Param = nullptr;
	m_Mover = nullptr;
	m_Collision = nullptr;
}

EnemyBase::~EnemyBase()
{
	Fin();
}

void EnemyBase::Step()
{
}

void EnemyBase::Update()
{
	// Z座標はMoverを無視する
	float z = m_Pos.z;

	// Moverで移動
	if (m_Mover)
	{
		m_Mover->Update();

		// Moverが終了したら参照を切る
		if (!m_Mover->IsActive())
		{
			m_Mover = nullptr;
		}
	}

	// Z座標はMoverを無視して移動量だけ
	m_Pos.z = z + m_Move.z;

	// プレイヤーのZ座標分だけ手前に描画する
	VECTOR playerPos = PlayerManager::GetInstance()->GetPlayer()->GetPos();
	m_DrawPos = m_Pos;
	m_DrawPos.z -= playerPos.z;

	MV1SetPosition(m_Handle, m_DrawPos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
}

void EnemyBase::Draw()
{
	MV1DrawModel(m_Handle);
}

void EnemyBase::Fin()
{
	MV1DeleteModel(m_Handle);
}

void EnemyBase::HitBullet(BulletBase* bullet)
{
	int damage = bullet->GetDamage();
	m_Hp -= damage;
}

void EnemyBase::Setup()
{
	m_Hp = m_Param->hp;
	m_Interval = m_Param->interval;
}

void EnemyBase::Dead()
{
	m_Active = false;
	m_Collision->SetActive(false);

	// 死亡エフェクト
	EffekseerManager::GetInstance()->PlayEffect3D(m_DeadEffectID, m_Pos);
}

void EnemyBase::SetMover(ObjectMoverBase* mover)
{
	m_Mover = mover;
	m_Mover->SetObjectPos(&m_Pos);
	m_Mover->Play();
}
