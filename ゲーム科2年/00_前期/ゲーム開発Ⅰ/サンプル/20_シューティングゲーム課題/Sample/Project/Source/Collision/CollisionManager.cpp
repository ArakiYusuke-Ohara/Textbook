#include "CollisionManager.h"
#include "CollisionBase.h"
#include "CollisionAABB.h"
#include "CollisionSphere.h"
#include "../Player/PlayerManager.h"
#include "../Enemy/EnemyManager.h"
#include "../Enemy/EnemyBase.h"
#include "../Bullet/BulletManager.h"
#include "../Bullet/BulletBase.h"
#include "../Block/BlockManager.h"
#include "../Player/Player.h"
#include "../Block/Block.h"


// 静的変数の初期化
CollisionManager* CollisionManager::m_Instance = nullptr;

// コンストラクタ
CollisionManager::CollisionManager()
{
}

// デストラクタ
CollisionManager::~CollisionManager()
{
	// 削除時の後始末忘れを防止する
	Fin();
}

void CollisionManager::Draw()
{
	for (CollisionBase* collision : m_Collisions)
	{
		if (collision->IsActive())
		{
			collision->Draw();
		}
	}
}

void CollisionManager::Fin()
{
	for (CollisionBase* collision : m_Collisions)
	{
		delete collision;
	}

	m_Collisions.clear();
}

CollisionAABB* CollisionManager::CreateAABB()
{
	return static_cast<CollisionAABB*>(CreateCollision(COLLISION_AABB));
}

CollisionSphere* CollisionManager::CreateSphere()
{
	return static_cast<CollisionSphere*>(CreateCollision(COLLISION_SPHERE));
}

CollisionBase* CollisionManager::CreateCollision(int id)
{
	// 同じIDかつ未使用のコリジョンを探す
	for (CollisionBase* collision : m_Collisions)
	{
		// typeidを使うと型が同じかチェックできる
		if (!collision->IsActive() && id == collision->GetID())
		{
			// 未使用のコリジョンを再利用する
			collision->SetActive(true);
			return collision;
		}
	}

	// 再利用できなければ追加する
	CollisionBase* collision = nullptr;
	switch (id)
	{
		case COLLISION_AABB: collision = new CollisionAABB; break;
		case COLLISION_SPHERE: collision = new CollisionSphere; break;
	}

	if (collision)
	{
		collision->SetActive(true);
	}

	// 管理配列に格納
	m_Collisions.push_back(collision);

	return collision;
}

void CollisionManager::CheckCollision()
{
	Player* player = PlayerManager::GetInstance()->GetPlayer();
	CollisionSphere* playerCollision = player->GetCollision();
	auto enemyList = EnemyManager::GetInstance()->GetEnemyList();
	auto bullets = BulletManager::GetInstance()->GetBullets();

	// 弾の当たり判定
	for (BulletBase* bullet : bullets)
	{
		if (!bullet->IsActive()) continue;

		CollisionSphere* bulletCollision = bullet->GetCollision();

		// プレイヤーの弾と
		if (bulletCollision->GetTag() == COLLISION_TAG_PLAYER_BULLET)
		{
			// エネミーの当たり判定
			for (EnemyBase* enemy : enemyList)
			{
				if (enemy->IsActive())
				{
					CollisionSphere* enemyCollision = enemy->GetCollision();
					if (bulletCollision->CheckSphere(enemyCollision))
					{
						enemy->HitBullet(bullet);
						bullet->HitEnemy();
					}
				}
			}
		}
		// エネミーの弾と
		else if (bulletCollision->GetTag() == COLLISION_TAG_ENEMY_BULLET)
		{
			// プレイヤーの当たり判定
			if (player->IsActive() && !player->IsInvisible())
			{
				if (bulletCollision->CheckSphere(playerCollision))
				{
					player->HitEnemyBullet(bullet);
					bullet->HitPlayer();
				}
			}
		}
	}
}
