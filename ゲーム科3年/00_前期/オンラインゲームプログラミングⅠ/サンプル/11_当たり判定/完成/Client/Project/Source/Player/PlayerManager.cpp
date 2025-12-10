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

NetworkPlayer& PlayerManager::CreateNetworkPlayer(const Client* client, int id, bool isSelf)
{
	// 生成して初期化～開始
	UniquePtr<NetworkPlayer> player = MakeUnique<NetworkPlayer>(client, id, isSelf);
	player->Init();
	player->Load();
	player->Start();

	// 末尾に格納
	m_Players.push_back(std::move(player));

	// 実は参照渡しの方が安全
	return *static_cast<NetworkPlayer*>(m_Players.back().get());
}

/// <summary>
/// プレイヤーを追加する
/// </summary>
/// <param name="client">通信に使われているクライアントクラス</param>
/// <param name="data">ログインデータ</param>
void PlayerManager::Login(const Client* client, Network::LoginData data)
{
	// 既に参加済みのプレイヤーも含め生成
	for (int i = 0; i < NETWORK_PLAYER_MAX; i++)
	{
		int id = data.playerID[i];
		if (id < 0) continue;

		bool isSelf = id == data.selfID;
		CreateNetworkPlayer(client, id, isSelf);
	}
}

void PlayerManager::Join(Network::JoinData data)
{
	// 参加プレイヤーを生成
	CreateNetworkPlayer(nullptr, data.playerID, false);
}

/// <summary>
/// ログアウト
/// </summary>
/// <param name="data">ログアウトするプレイヤーのID</param>
void PlayerManager::Logout(Network::LogoutData data)
{
	// IDが一致したプレイヤーはログアウトするので削除
	for (auto itr = m_Players.begin(); itr != m_Players.end(); itr++)
	{
		const NetworkPlayer* nwPlayer = static_cast<NetworkPlayer*>((*itr).get());

		if (nwPlayer->GetID() == data.playerID)
		{
			m_Players.erase(itr);
			break;
		}
	}
}

/// <summary>
/// 座標を同期する
/// </summary>
/// <param name="data">座標データ</param>
void PlayerManager::SyncTransform(Network::AllTransformData data)
{
	// 全プレイヤーのトランスフォームをサーバーから受信したものにする
	int i = 0;
	for (auto& player : m_Players)
	{
		NetworkPlayer* nwPlayer = static_cast<NetworkPlayer*>(player.get());
		nwPlayer->SetServerPos(data.pos[i]);
		nwPlayer->SetServerRot(data.rot[i]);
		nwPlayer->SetServerScale(data.scale[i]);
		i++;
	}
}

/// <summary>
/// プレイヤーを死亡させる
/// </summary>
/// <param name="playerID">死亡させるプレイヤーID</param>
void PlayerManager::DiePlayer(int playerID)
{
	// IDが一致したプレイヤーを死亡させる
	for (auto itr = m_Players.begin(); itr != m_Players.end(); itr++)
	{
		NetworkPlayer* nwPlayer = static_cast<NetworkPlayer*>((*itr).get());

		if (nwPlayer->GetID() == playerID)
		{
			nwPlayer->Die();
			break;
		}
	}
}
