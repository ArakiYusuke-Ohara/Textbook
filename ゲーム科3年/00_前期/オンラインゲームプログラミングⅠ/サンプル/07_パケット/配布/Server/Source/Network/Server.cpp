#include "DxLib.h"
#include "Server.h"
#include "NetworkCommonParam.h"
#include <vector>

using namespace Network;

Server::Server()
{
	m_NetworkPlayerData = {};
}

Server::~Server()
{
	Fin();
}

void Server::Init()
{
	// 接続してくるのを待つ状態にする
	int success = PreparationListenNetWork(PORT_NUMBER);
}

void Server::Update()
{
	// 新しい接続があったらそのネットワークハンドルを得る
	int acceptHandle = GetNewAcceptNetWork();
	// 新しい接続があった
	if (acceptHandle != -1)
	{
		AddUserData(acceptHandle);
	}

	// 切断があったらそのネットワークハンドルを得る
	int lostHandle = GetLostNetWork();
	// 切断があった
	if (lostHandle != -1)
	{
		RemoveUserData(lostHandle);
	}
}

void Server::Draw()
{
}

void Server::Fin()
{
	m_NetworkPlayerData.clear();
}

/// <summary>
/// ユーザーデータを追加する
/// </summary>
/// <param name="handle">追加するユーザーのハンドル</param>
void Server::AddUserData(int handle)
{
	NetworkPlayerData player = {};

	player.id = (int)m_NetworkPlayerData.size();
	player.client.handle = handle;
	// 接続してきたマシンのＩＰアドレスを得る
	GetNetWorkIP(handle, &player.client.ip);

	// 初期設定
	player.pos = { 100.0f, 100.0f, 0.0f };
	player.scale = { 1.0f, 1.0f, 1.0f };

	// ユーザー配列に追加
	m_NetworkPlayerData.push_back(player);
}

/// <summary>
/// ユーザーデータを取り除く
/// </summary>
/// <param name="handle">取り除くユーザーのハンドル</param>
void Server::RemoveUserData(int handle)
{
	// イテレータを使って部分削除する
	for(auto itr = m_NetworkPlayerData.begin(); itr != m_NetworkPlayerData.end(); itr++)
	{
		const NetworkPlayerData& player = (*itr);
		// 削除するユーザーをハンドルから検索
		if (player.client.handle == handle)
		{
			// 見つかったら削除して終了
			m_NetworkPlayerData.erase(itr);
			return;
		}
	}
}

