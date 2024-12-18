#include "BlockManager.h"
#include "Block.h"

// 静的変数の初期化
BlockManager* BlockManager::m_Instance = nullptr;

// コンストラクタ
BlockManager::BlockManager()
{

}

// デストラクタ
BlockManager::~BlockManager()
{
	// 削除時の後始末忘れを防止する
	Fin();
}

void BlockManager::Init()
{

}

void BlockManager::Load()
{

}

void BlockManager::Start()
{
	// 初期位置一覧
	const VECTOR DEFAULT_POS[BLOCK_MAX] =
	{
		{-3.0f, 1.0f,  3.0f},
		{ 3.0f, 1.0f,  3.0f},
		{-3.0f, 1.0f, -3.0f},
		{ 3.0f, 1.0f, -3.0f},
	};

}

void BlockManager::Step()
{

}

void BlockManager::Update()
{

}

void BlockManager::Draw()
{

}

void BlockManager::Fin()
{

}
