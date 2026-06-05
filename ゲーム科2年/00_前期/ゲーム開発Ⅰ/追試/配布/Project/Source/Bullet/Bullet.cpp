#include "Bullet.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionSphere.h"

constexpr int LIFE = 60;
constexpr float RAD = 0.125f;

Bullet::Bullet()
: m_Active(false)
, m_Pos()
, m_Rot()
, m_Move()
, m_Life(0)
, m_Rad(0.0f)
, m_Speed(0.0f)
, m_Collision(nullptr)
{
}

Bullet::~Bullet()
{
}

void Bullet::Init()
{
	m_Rad = RAD;

	m_Collision = CollisionManager::GetInstance()->CreateSphere();
	m_Collision->SetTargetPos(&m_Pos);
	m_Collision->SetRadius(m_Rad);
}

void Bullet::Step()
{
	if (!m_Active) return;

	m_Pos = MyMath::VecAdd(m_Pos, m_Move);
	
	// 寿命処理
	m_Life--;
	if (m_Life <= 0)
	{
		m_Active = false;
		m_Collision->SetActive(false);
	}
}

void Bullet::Draw()
{
	if (m_Active)
	{
		DrawSphere3D(m_Pos, m_Rad, 36, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
	}
}

/// <summary>
/// 発射処理
/// </summary>
/// <param name="pos">発射位置</param>
/// <param name="rot">回転向き</param>
/// <param name="speed">速度</param>
void Bullet::Fire(VECTOR pos, VECTOR rot, float speed)
{
	m_Active = true;
	m_Pos = pos;
	m_Rot = rot;
	m_Speed = speed;
	m_Life = LIFE;

	// 課題３：rotもしくはm_Rotから弾丸の移動ベクトルを計算する


	// 課題４：移動量にスピードをスカラー倍する


	m_Collision->SetActive(true);
}

void Bullet::Hit()
{
	m_Active = false;
	m_Collision->SetActive(false);
}
