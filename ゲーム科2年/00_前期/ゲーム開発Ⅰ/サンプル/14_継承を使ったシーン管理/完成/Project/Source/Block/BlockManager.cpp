#include "BlockManager.h"
#include "Block.h"

// 静的変数の初期化
BlockManager* BlockManager::m_Instance = nullptr;

// コンストラクタ
BlockManager::BlockManager()
{
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		m_Blocks[i] = nullptr;
	}
	m_Handle = 0;
}

// デストラクタ
BlockManager::~BlockManager()
{
	// 削除時の後始末忘れを防止する
	Fin();
}

void BlockManager::Init()
{
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		m_Blocks[i] = new Block;
	}
}

void BlockManager::Load()
{
	// 同じモデルを複数使用する場合は、
	// まず1つだけロードして大元のモデルとする
	m_Handle = MV1LoadModel("Data/Block/Block.x");

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		// 引数で大元のモデルハンドルを渡して
		// Box側で複製する
		m_Blocks[i]->Load(m_Handle);
	}
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

	// 各ボックスを開始して配置
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		m_Blocks[i]->Start();
		m_Blocks[i]->SetPos(DEFAULT_POS[i]);
	}
}

void BlockManager::Step()
{
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		m_Blocks[i]->Step();
	}
}

void BlockManager::Update()
{
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		m_Blocks[i]->Update();
	}
}

void BlockManager::Draw()
{
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		m_Blocks[i]->Draw();
	}
}

void BlockManager::Fin()
{
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		delete m_Blocks[i];
	}
}
