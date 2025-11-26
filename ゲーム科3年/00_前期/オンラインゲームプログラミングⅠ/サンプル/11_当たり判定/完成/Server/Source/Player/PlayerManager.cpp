#include "PlayerManager.h"

Player& PlayerManager::CreatePlayer()
{
	// プレイヤーを生成して動的配列に追加
	m_Players.push_back(MakeShared<Player>());
	// 生成したプレイヤーの参照を返す
	return *m_Players.back().get();
}
