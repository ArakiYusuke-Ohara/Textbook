#include "PlayerManager.h"
#include "Player.h"

// 静的変数の初期化
PlayerManager* PlayerManager::m_Instance = nullptr;

// コンストラクタ
PlayerManager::PlayerManager()
{
	// 生成されていなければnullptr
	m_Player = nullptr;
}

// メンバーにスマートポインタがある場合は、
// 空でも定義が必要(defaultだと安全)
PlayerManager::~PlayerManager() = default;

void PlayerManager::CreatePlayer()
{
	// プレイヤーが生成されていなければ生成する
	if (!m_Player)
	{
		m_Player = MakeUnique<Player>();
	}
}

void PlayerManager::Init()
{
	if (m_Player)
	{
		m_Player->Init();
	}
}

void PlayerManager::Load()
{
	if (m_Player)
	{
		m_Player->Load();
	}
}

void PlayerManager::Start()
{
	if (m_Player)
	{
		m_Player->Start();
	}
}

void PlayerManager::Step()
{
	if (m_Player)
	{
		m_Player->Step();
	}
}

void PlayerManager::Update()
{
	if (m_Player)
	{
		m_Player->Update();
	}
}

void PlayerManager::Draw()
{
	if (m_Player)
	{
		m_Player->Draw();
	}
}
