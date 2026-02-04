#include "BlockManager.h"
#include "Block.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"

#define BLOCK_ACTIVE_DISTANCE 100.0f

// 静的変数の初期化
BlockManager* BlockManager::m_Instance = nullptr;

// データ群はエクセルにしたい
const BlockParameter BLOCK_MASTER_PARAM[] =
{
	{-2.0f, 0.0f, 99999999.0f},
	//{ 2.0f, 0.0f, 200.0f},
	//{ 0.0f, 0.0f, 300.0f},
};

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
	m_OriginalBlock->Init();
}

void BlockManager::Load()
{
	m_OriginalBlock->Load();
}

void BlockManager::Start()
{
	for (BlockParameter param : BLOCK_MASTER_PARAM)
	{
		m_BlockParamList.push_back(param);
	}
}

void BlockManager::Step()
{
	// ブロック生成システムをステップ
	StepBlockCreater();

	for (Block* block : m_Blocks)
	{
		if (block->IsActive())
		{
			block->Step();
		}
	}
}

void BlockManager::Update()
{
	for (Block* block : m_Blocks)
	{
		if (block->IsActive())
		{
			block->Update();
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

void BlockManager::StepBlockCreater()
{
	Player* player = PlayerManager::GetInstance()->GetPlayer();
	VECTOR playerPos = player->GetPos();

	for (auto itr = m_BlockParamList.begin(); itr != m_BlockParamList.end(); )
	{
		BlockParameter param = (*itr);

		// Z座標が一定距離になったら生成
		if ((param.pos.z - playerPos.z) <= BLOCK_ACTIVE_DISTANCE)
		{
			Block* block = CreateBlock();
			block->SetPos(param.pos);

			// 一度使ったパラメータはもう使わないので削除
			itr = m_BlockParamList.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}
