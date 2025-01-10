#include "EnemyBoss.h"
#include "../Collision/CollisionManager.h"

EnemyBoss::EnemyBoss()
{
}

EnemyBoss::~EnemyBoss()
{
}

void EnemyBoss::Init()
{
}

void EnemyBoss::Load()
{
	m_Handle = MV1LoadModel("Data/Enemy/Boss/Boss.x");
}

void EnemyBoss::Start()
{
}

void EnemyBoss::Step()
{
}

void EnemyBoss::Dead()
{
}

EnemyBase* EnemyBoss::Clone()
{
	EnemyBoss* clone = new EnemyBoss;
	*clone = *this;

	// 画像はDuplicateする必要がある
	clone->m_Handle = MV1DuplicateModel(m_Handle);

	// くらい判定
	clone->m_Collision = CollisionManager::GetInstance()->CreateSphere();

	// 出来上がったクローンを返却
	return clone;
}

void EnemyBoss::RedShot()
{
}

void EnemyBoss::GreenShot()
{
}

void EnemyBoss::BlueShot()
{

}
void EnemyBoss::YellowShot()
{
}

void EnemyBoss::MainShot()
{
}

