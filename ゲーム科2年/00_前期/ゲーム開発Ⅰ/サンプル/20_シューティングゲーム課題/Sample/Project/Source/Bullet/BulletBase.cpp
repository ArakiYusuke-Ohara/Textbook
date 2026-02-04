#include "BulletBase.h"
#include "BulletParameter.h"
#include "BulletManager.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionSphere.h"
#include "../MyEffekseer/EffekseerManager.h"

BulletBase::BulletBase()
{
	m_Id = 0;
	m_Handle = 0;
	m_Life = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_Radius = 0.0f;
	m_Active = false;
	m_Param = nullptr;
	m_Collision = nullptr;
}

BulletBase::~BulletBase()
{
	Fin();
}

void BulletBase::Init(int id)
{
	m_Id = id;
	m_Param = BulletManager::GetInstance()->GetBulletParameter(m_Id);
}

void BulletBase::Load()
{
	// パラメータを元にロード
	m_Handle = MV1LoadModel(m_Param->path);
}

void BulletBase::Step()
{
	// 寿命を減らす
	m_Life--;

	if (m_Life <= 0)
	{
		m_Active = false;
		// 当たり判定も非アクティブにする
		m_Collision->SetActive(false);
	}
}

void BulletBase::Fin()
{
	MV1DeleteModel(m_Handle);
}

void BulletBase::Fire(VECTOR pos, VECTOR vec)
{
	m_Active = true;
	m_Pos = pos;
	m_Move = MyMath::VecNormalize(vec);
	m_Move = MyMath::VecScale(m_Move, m_Param->speed);
	m_Life = m_Param->life;
	m_Radius = m_Param->radius;
	CollisionSphere* collision = CollisionManager::GetInstance()->CreateSphere();
	collision->SetRadius(m_Param->radius);
	collision->SetTargetPos(&m_Pos);
	collision->SetTag(m_Param->collisionTag);
	m_Collision = collision;
}

void BulletBase::HitPlayer()
{
	m_Active = false;
	m_Collision->SetActive(false);
}

void BulletBase::HitEnemy()
{
	m_Active = false;
	m_Collision->SetActive(false);

	EffekseerManager::GetInstance()->PlayEffect3D(m_Param->hitEffect, m_Pos);
}
