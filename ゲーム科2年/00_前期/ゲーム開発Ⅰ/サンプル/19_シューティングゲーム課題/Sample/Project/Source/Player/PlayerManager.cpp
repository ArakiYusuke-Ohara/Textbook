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

// デストラクタ
PlayerManager::~PlayerManager()
{
	// 削除時の後始末忘れを防止する
	Fin();
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
		if (m_Player->IsActive())
		{
			m_Player->Step();
		}
	}
}

void PlayerManager::Update()
{
	if (m_Player)
	{
		if (m_Player->IsActive())
		{
			m_Player->Update();
		}
	}
}

void PlayerManager::Draw()
{
	if (m_Player)
	{
		if (m_Player->IsActive())
		{
			m_Player->Draw();
		}
	}
}

void PlayerManager::Fin()
{
	if (m_Player)
	{
		m_Player->Fin();
	}
}

void PlayerManager::CreatePlayer()
{
	// プレイヤーが生成されていなければ生成する
	if (!m_Player)
	{
		m_Player = new Player;
	}
}

// プレイヤーは奥には移動していないので
// それを前提とした座標を計算する
VECTOR PlayerManager::ConvertPlayerLocalPos(VECTOR pos)
{
	if (!m_Player) return VGet(0.0f, 0.0f, 0.0f);

	VECTOR result = pos;
	result.z -= m_Player->GetPos().z;

	return result;
}

void PlayerManager::CheckHP()
{
	if (m_Player)
	{
		if (m_Player->IsActive() && m_Player->GetHP() <= 0)
		{
			m_Player->Dead();
		}
	}
}