#include "CollisionManager.h"
#include "CollisionBase.h"
#include "CollisionAABB.h"
#include "CollisionSphere.h"
#include "../Player/PlayerManager.h"
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
	auto players = PlayerManager::GetInstance()->GetPlayers();
	auto blocks = BlockManager::GetInstance()->GetBlocks();

	for (Player* player : players)
	{
		CollisionAABB* playerCollision = player->GetCollision();
		for (Block* block : blocks)
		{
			CollisionAABB* blockCollision = block->GetCollision();
			if (blockCollision->CheckAABB(playerCollision))
			{
				player->HitBlock(block);
			}
		}
	}
}
