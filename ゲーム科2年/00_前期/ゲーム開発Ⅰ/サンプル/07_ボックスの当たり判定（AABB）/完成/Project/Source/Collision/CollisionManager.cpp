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
	m_AABB = {};
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
	for (CollisionAABB* aabb : m_AABB)
	{
		if (aabb)
		{
			aabb->Draw();
		}
	}
}

void CollisionManager::Fin()
{
	for (CollisionAABB* aabb : m_AABB)
	{
		delete aabb;
	}

	m_AABB.clear();
}

CollisionAABB* CollisionManager::CreateAABB()
{
	CollisionAABB* aabb = new CollisionAABB;
	m_AABB.push_back(aabb);

	return aabb;
}
