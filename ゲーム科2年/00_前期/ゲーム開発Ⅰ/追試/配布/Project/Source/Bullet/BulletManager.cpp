#include "BulletManager.h"
#include "Bullet.h"
#include "../Enemy/EnemyManager.h"
#include "../Collision/CollisionSphere.h"

BulletManager* BulletManager::m_Instance = nullptr;

BulletManager::BulletManager()
: m_Bullets()
{
}

void BulletManager::Step()
{
	for (Bullet* bullet : m_Bullets)
	{
		bullet->Step();
	}
}

void BulletManager::Update()
{
	// “G‚Æ’eŠÛ‚Ì“–‚½‚è”»’è
	auto enemyList = EnemyManager::GetInstance()->GetEnemyList();
	for (EnemyBase* enemy : enemyList)
	{
		if (!enemy->IsActive()) continue;

		for (Bullet* bullet : m_Bullets)
		{
			if (!bullet->IsActive()) continue;
			CollisionSphere* enemyCollision = enemy->GetCollision();
			CollisionSphere* bulletCollision = bullet->GetCollision();

			if (bulletCollision->CheckSphere(enemyCollision))
			{
				bullet->Hit();
				enemy->Damage();
			}
		}
	}
}

void BulletManager::Draw()
{
	for (Bullet* bullet : m_Bullets)
	{
		bullet->Draw();
	}
}

Bullet* BulletManager::FireBullet(VECTOR pos, VECTOR rot, float speed)
{
	for (Bullet* bullet : m_Bullets)
	{
		if (!bullet->IsActive())
		{
			bullet->Fire(pos, rot, speed);
			return bullet;
		}
	}

	Bullet* bullet = new Bullet;
	bullet->Init();
	bullet->Fire(pos, rot, speed);
	m_Bullets.push_back(bullet);

	return bullet;
}
