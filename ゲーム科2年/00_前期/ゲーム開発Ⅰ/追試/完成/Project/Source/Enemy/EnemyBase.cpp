#include "EnemyBase.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionSphere.h"

constexpr int HP = 3;
constexpr float RAD = 0.5f;

EnemyBase::EnemyBase()
{
	m_Active = false;
	m_Handle = 0;
	m_HP = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_Collision = nullptr;
}

EnemyBase::~EnemyBase()
{
	Fin();
}

void EnemyBase::Update()
{
	if (!m_Active) return;

	m_Pos = MyMath::VecAdd(m_Pos, m_Move);

	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
}

void EnemyBase::Draw()
{
	if (!m_Active) return;

	MV1DrawModel(m_Handle);
}

void EnemyBase::Fin()
{
	MV1DeleteModel(m_Handle);
}

void EnemyBase::Activate()
{
	m_Active = true;
	m_HP = HP;
	if (!m_Collision)
	{
		m_Collision = CollisionManager::GetInstance()->CreateSphere();
		m_Collision->SetTargetPos(&m_Pos);
		m_Collision->SetLocalPos(VGet(0.0f, 0.5f, 0.0f));
		m_Collision->SetRadius(RAD);
	}
	m_Collision->SetActive(true);
}

void EnemyBase::Damage(int damage)
{
	m_HP -= damage;

	if (m_HP <= 0)
	{
		m_Active = false;
		m_Collision->SetActive(false);
	}
}
