#include "BlockManager.h"
#include "Block.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../Stage/StageParameter.h"

#define BLOCK_ACTIVE_DISTANCE 100.0f
#define BLOCK_MAP_ROW 12
#define BLOCK_MAP_COL 16
#define BLOCK_WIDTH 40
#define BLOCK_HEIGHT 40

const short int BLOCK_MAP[BLOCK_MAP_ROW][BLOCK_MAP_COL] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};


// 静的変数の初期化
BlockManager* BlockManager::m_Instance = nullptr;

// コンストラクタ
BlockManager::BlockManager()
{
	m_OriginalBlock = nullptr;
}

// デストラクタ
BlockManager::~BlockManager()
{
	// 削除時の後始末忘れを防止する
	Fin();
}

void BlockManager::Init()
{
	m_OriginalBlock = new Block;
}

void BlockManager::Load()
{
	m_OriginalBlock->Load();
}

void BlockManager::Start()
{
	// 配置処理
	for (int i = 0; i < BLOCK_MAP_ROW; i++)
	{
		for (int j = 0; j < BLOCK_MAP_COL; j++)
		{
			if (BLOCK_MAP[i][j] == 1)
			{
				Block* block = CreateBlock();
				block->SetPos(VGet((float)(STAGE_POS_X + j * BLOCK_WIDTH), (float)(STAGE_POS_Y + i * BLOCK_HEIGHT), 0.0f));
				block->Start();
			}
		}
	}
}

void BlockManager::Draw()
{
	for (Block* block : m_Blocks)
	{
		if (block->IsActive())
		{
			block->Draw();
		}
	}
}

void BlockManager::Fin()
{
	for (Block* block : m_Blocks)
	{
		delete block;
	}

	m_Blocks.clear();

	delete m_OriginalBlock;
}

Block* BlockManager::CreateBlock()
{
	// 未使用のブロックを探す
	for (Block* block : m_Blocks)
	{
		if (!block->IsActive())
		{
			block->SetActive(true);
			return block;
		}
	}

	// 未使用のブロックがなければ追加する
	Block* block = m_OriginalBlock->Clone();
	block->SetActive(true);
	m_Blocks.push_back(block);

	return block;
}
