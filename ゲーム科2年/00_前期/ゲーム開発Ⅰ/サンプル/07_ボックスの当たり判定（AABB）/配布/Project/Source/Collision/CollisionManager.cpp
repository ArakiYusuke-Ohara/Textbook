#include "CollisionManager.h"
#include "CollisionAABB.h"
#include "../Player/PlayerManager.h"
#include "../Block/BlockManager.h"
#include "../Block/Block.h"

// 静的変数の初期化
CollisionManager* CollisionManager::m_Instance = nullptr;

// コンストラクタ
CollisionManager::CollisionManager()
{
	// m_AABB配列を先頭から末尾までまわす範囲for文
	for(int i = 0 ; i < COLLISION_MAX; i++)
	{
		m_AABB[i] = nullptr;
	}
}

// デストラクタ
CollisionManager::~CollisionManager()
{
	// 削除時の後始末忘れを防止する
	Fin();
}

void CollisionManager::Draw()
{
	// m_AABBを先頭から末尾までまわす範囲for文
	for (auto aabb : m_AABB)
	{
		if (aabb)
		{
			aabb->Draw();
		}
	}
}

void CollisionManager::Fin()
{
	for (int i = 0; i < COLLISION_MAX; i++)
	{
		// 使用されているところだけ削除して未使用状態にする
		if (m_AABB[i])
		{
			delete m_AABB[i];
			m_AABB[i] = nullptr;
		}
	}
}

CollisionAABB* CollisionManager::CreateAABB()
{
	CollisionAABB* result = nullptr;

	// m_AABBを先頭から末尾までまわす範囲for文
	for (int i = 0; i < COLLISION_MAX; i++)
	{
		// 未使用のAABBか
		if (!m_AABB[i])
		{
			// AABBを生成して配列に保存
			m_AABB[i] = result = new CollisionAABB;
			break;
		}
	}

	return result;
}

void CollisionManager::DeleteAABB(CollisionAABB* targetAABB)
{
	// m_AABBを先頭から末尾までまわす範囲for文
	for (auto aabb : m_AABB)
	{
		// 参照先が一致するAABBを探す
		if (aabb == targetAABB)
		{
			// 見つかったら削除
			delete targetAABB;
			// 未使用状態にするためnullptr
			aabb = nullptr;
			break;
		}
	}
}

void CollisionManager::CheckCollision()
{
	Player* player = PlayerManager::GetInstance()->GetPlayer();
	Block** blocks = BlockManager::GetInstance()->GetBlock();
	CollisionAABB* playerAABB = player->GetAABB();

	// ブロックとプレイヤーの当たり判定
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		Block* block = blocks[i];
		CollisionAABB* blockAABB = block->GetAABB();

		if (playerAABB->CheckAABB(blockAABB))
		{
			// 当たった時の処理
			player->HitBlock(blockAABB);
		}
	}
}
