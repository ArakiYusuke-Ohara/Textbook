#include "EnemyDia.h"
#include "../Collision/CollisionManager.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../MyEffekseer/EffekseerManager.h"
#include "../MyEffekseer/EffekseerEffectBase.h"
#include "../Collision/CollisionSphere.h"
#include "../Easing/EasingManager.h"
#include "../Easing/Easing.h"
#include "../Bullet/BulletManager.h"
#include "../Bullet/BulletBase.h"
#include "../MyMath/MyMath.h"

#define DIA_BULLET_ID 2

EnemyDia::EnemyDia()
{
	m_IsBarrier = false;
	m_BarrierHandle = 0;
	m_BarrierTimer = 0;
	m_BarrierScale = 0.0f;
	m_BarrierEffect = nullptr;
	m_BarrierEasing = nullptr;
}

EnemyDia::~EnemyDia()
{
}

void EnemyDia::Init()
{
	BulletManager::GetInstance()->SetupBullet(DIA_BULLET_ID);
	m_DeadEffectID = EFFEKSEER_BEE_DEAD;
}

void EnemyDia::Load()
{
	m_Handle = MV1LoadModel("Data/Enemy/Dia/Dia.x");
	m_BarrierHandle = MV1LoadModel("Data/Enemy/Dia/Barrier.x");
}

void EnemyDia::Start()
{
	m_Collision->SetActive(true);
	m_Collision->SetTargetPos(&m_Pos);
	m_Collision->SetRadius(m_Param->radius);
	m_Collision->SetTag(COLLISION_TAG_ENEMY);

	m_BarrierEffect = EffekseerManager::GetInstance()->PlayEffect3D(EFFEKSEER_BARRIER, m_Pos);

	m_BarrierEasing = EasingManager::GetInstance()->CreateEasing();

}

void EnemyDia::Step()
{
	if (m_BarrierTimer <= 0)
	{
		if (m_IsBarrier)
		{
			m_BarrierEasing->Play(EASE_IN_SLIDE, 10, true);
			m_IsBarrier = false;
			m_Interval = m_Param->interval;
		}
		else
		{
			m_BarrierEasing->Play(EASE_IN_SLIDE, 10);
			m_IsBarrier = true;
		}
		m_BarrierTimer = 180;
	}
	else
	{
		m_BarrierTimer--;
	}
	m_BarrierScale = m_BarrierEasing->GetValue();

	if (!m_IsBarrier)
	{
		if (m_Interval <= 0)
		{
			// プレイヤーに向けて発射
			VECTOR playerPos = PlayerManager::GetInstance()->GetPlayer()->GetPos();
			VECTOR bulletVec = MyMath::VecCreate(m_Pos, playerPos);
			BulletManager::GetInstance()->FireBullet(DIA_BULLET_ID, m_Pos, bulletVec);
			m_Interval = m_Param->interval;
		}
		else
		{
			m_Interval--;
		}
	}
}

void EnemyDia::Update()
{
	EnemyBase::Update();

	if (m_BarrierEffect)
	{
		m_BarrierEffect->SetPos(m_DrawPos);
		m_BarrierEffect->SetScale(VGet(m_BarrierScale, m_BarrierScale, m_BarrierScale));
	}
}

void EnemyDia::Dead()
{
	EnemyBase::Dead();
	if (m_BarrierEffect) m_BarrierEffect->Stop();
}

// 呼ばれたオブジェクトの複製を作る関数
EnemyBase* EnemyDia::Clone()
{
	// クローン用のオブジェクトを生成
	EnemyDia* clone = new EnemyDia;

	// 自身の中身をクローンにコピー
	*clone = *this;

	// 画像はDuplicateする必要がある
	clone->m_Handle = MV1DuplicateModel(m_Handle);
	clone->m_BarrierHandle = MV1DuplicateModel(m_BarrierHandle);

	// くらい判定
	clone->m_Collision = CollisionManager::GetInstance()->CreateSphere();

	// 出来上がったクローンを返却
	return clone;
}

void EnemyDia::HitBullet(BulletBase* bullet)
{
	if (!m_IsBarrier)
	{
		int damage = bullet->GetDamage();
		m_Hp -= damage;
	}
	else
	{
		EffekseerManager::GetInstance()->PlayEffect3D(EFFEKSEER_GUARD, bullet->GetPos());
	}
}
