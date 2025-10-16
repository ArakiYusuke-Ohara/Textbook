#include "PlayerManager.h"
#include "Player.h"
#include "NetworkPlayer.h"
#include "../Network/Client.h"

PlayerManager::PlayerManager()
{
}

PlayerManager::~PlayerManager() = default;

void PlayerManager::Load()
{
	for (auto& player : m_Players)
	{
		player->Load();
	}
}

void PlayerManager::Start()
{
	for (auto& player : m_Players)
	{
		player->Start();
	}
}

void PlayerManager::Step()
{
	for (auto& player : m_Players)
	{
		player->Step();
	}
}

void PlayerManager::Draw()
{
	for (auto& player : m_Players)
	{
		player->Draw();
	}
}

Player& PlayerManager::CreatePlayer()
{
	// 生成して初期化
	UniquePtr<Player> player = MakeUnique<Player>();
	player->Init();

	// 末尾に格納
	m_Players.push_back(std::move(player));

	// 実は参照渡しの方が安全
	return *(m_Players.back().get());
}

NetworkPlayer& PlayerManager::CreateNetworkPlayer(Client& client)
{
	// 生成して初期化
	UniquePtr<NetworkPlayer> player = MakeUnique<NetworkPlayer>(client);
	player->Init();

	// 末尾に格納
	m_Players.push_back(std::move(player));

	// 実は参照渡しの方が安全
	return *static_cast<NetworkPlayer*>(m_Players.back().get());
}

void PlayerManager::AddEntryPlayer(int id)
{
	// 既にエントリー済みかチェック
	bool isEntry = false;
	for (auto& player : m_Players)
	{
		if (player->GetID() == id)
		{
			isEntry = true;
			break;
		}
	}

	// エントリー済みでなければ追加
	if (!isEntry)
	{
	}
}
