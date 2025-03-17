#include "PlayerManager.h"
#include "Player.h"
#include "AIPlayer.h"

// 静的変数の初期化
PlayerManager* PlayerManager::m_Instance = nullptr;

// コンストラクタ
PlayerManager::PlayerManager()
{
}

// デストラクタ
PlayerManager::~PlayerManager()
{
	// 削除時の後始末忘れを防止する
	Fin();
}

void PlayerManager::Init()
{
	m_Players.clear();
	m_Players.shrink_to_fit();
}

void PlayerManager::Load()
{
	for (Player* player : m_Players)
	{
		player->Load();
	}
}

void PlayerManager::Start()
{
	for (Player* player : m_Players)
	{
		player->Start();
	}
}

void PlayerManager::Step()
{
	for (Player* player : m_Players)
	{
		player->Step();
	}
}

void PlayerManager::Update()
{
	for (Player* player : m_Players)
	{
		player->Update();
	}
}

void PlayerManager::Draw()
{
	for (Player* player : m_Players)
	{
		player->Draw();
	}
}

void PlayerManager::Fin()
{
	for (Player* player : m_Players)
	{
		player->Fin();
	}

	m_Players.clear();
	m_Players.shrink_to_fit();
}

Player* PlayerManager::CreatePlayer(int number)
{
	Player* player = new Player;
	player->SetPlayerNumber(number);
	player->Init();
	m_Players.push_back(player);

	return player;
}

AIPlayer* PlayerManager::CreateAIPlayer(int number)
{
	AIPlayer* player = new AIPlayer;
	player->SetPlayerNumber(number);
	player->Init();
	m_Players.push_back(player);

	return player;
}
