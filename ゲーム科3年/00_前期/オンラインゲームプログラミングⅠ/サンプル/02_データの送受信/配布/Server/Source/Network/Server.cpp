#include "DxLib.h"
#include "Server.h"
#include "NetworkCommonParam.h"

Server::Server()
{
	m_ClientData = {};
	m_ClientChatData = {};
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
	// まだなにも送られてなければ描画しない
	if (strlen(m_ClientChatData.userName) <= 0) return;

	// 最後に送られたメッセージ内容を描画
	DrawFormatString(0, 0, GetColor(0, 255, 0), "%s", m_ClientChatData.userName);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "%s", m_ClientChatData.message);

}

void Server::Fin()
{
	m_ClientData.clear();
}

/// <summary>
/// ユーザーデータを追加する
/// </summary>
/// <param name="handle">追加するユーザーのハンドル</param>
void Server::AddUserData(int handle)
{
	ClientData client;

	client.handle = handle;
	// 接続してきたマシンのＩＰアドレスを得る
	GetNetWorkIP(handle, &client.ip);

	// ユーザー配列に追加
	m_ClientData.push_back(client);
}

/// <summary>
/// ユーザーデータを取り除く
/// </summary>
/// <param name="handle">取り除くユーザーのハンドル</param>
void Server::RemoveUserData(int handle)
{
	// イテレータを使って部分削除する
	for(auto itr = m_ClientData.begin(); itr != m_ClientData.end(); itr++)
	{
		// 削除するユーザーをハンドルから検索
		if ((*itr).handle == handle)
		{
			// 見つかったら削除して終了
			m_ClientData.erase(itr);
			return;
		}
	}
}
