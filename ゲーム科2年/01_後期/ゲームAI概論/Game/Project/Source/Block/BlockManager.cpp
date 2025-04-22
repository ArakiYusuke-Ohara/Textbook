#include "BlockManager.h"
#include "Block.h"
#include "BlockParameter.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../Stage/StageManager.h"
#include "../Stage/StageParameter.h"
#include "../Stage/Stage.h"

const short int BLOCK_MAP[BLOCK_MAP_ROW][BLOCK_MAP_COL] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
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
	Stage* stage = StageManager::GetInstance()->GetStage();
	float stagePosX = stage->GetPosX();
	float stagePosY = stage->GetPosY();

	// 配置処理
	for (int i = 0; i < BLOCK_MAP_ROW; i++)
	{
		for (int j = 0; j < BLOCK_MAP_COL; j++)
		{
			if (BLOCK_MAP[i][j] == 1)
			{
				Block* block = CreateBlock();
				block->SetPos(VGet((float)(stagePosX + j * BLOCK_WIDTH), (float)(stagePosY + i * BLOCK_HEIGHT), 0.0f));
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
