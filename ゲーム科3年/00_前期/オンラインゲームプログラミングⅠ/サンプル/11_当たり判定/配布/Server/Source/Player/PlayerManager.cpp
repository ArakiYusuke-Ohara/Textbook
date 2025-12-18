#include "PlayerManager.h"
#include "Player.h"

PlayerManager::PlayerManager()
{
	m_Players = {};
}

void PlayerManager::Draw()
{
	// 全プレイヤーの描画
	for (const auto& player : m_Players)
	{
		player->Draw();
	}
}

Player& PlayerManager::CreatePlayer()
{
	// プレイヤーを生成して動的配列に追加
	m_Players.push_back(MakeUnique<Player>());
	// 生成したプレイヤーの参照を返す
	return *m_Players.back().get();
}

void PlayerManager::RemovePlayer(int handle)
{
	// 指定IDのプレイヤーを削除
	for (auto itr = m_Players.begin(); itr != m_Players.end(); ++itr)
	{
		if ((*itr)->GetNetworkHandle() == handle)
		{
			m_Players.erase(itr);
			break;
		}
	}
}
