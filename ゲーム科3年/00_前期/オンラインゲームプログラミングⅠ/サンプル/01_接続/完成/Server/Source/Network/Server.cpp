#include "DxLib.h"
#include "Server.h"
#include "NetworkCommonParam.h"

Server::Server()
{
	m_UserData = {};
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
	// 接続中のユーザーの情報を描画
	int count = 0;
	for (UserData user : m_UserData)
	{
		DrawFormatString(0, count * 20, GetColor(255, 255, 255), "User%02d : %d.%d.%d.%d", count, user.ip.d1, user.ip.d2, user.ip.d3, user.ip.d4);
		count++;
	}
}

void Server::Fin()
{
	m_UserData.clear();
}

/// <summary>
/// ユーザーデータを追加する
/// </summary>
/// <param name="handle">追加するユーザーのハンドル</param>
void Server::AddUserData(int handle)
{
	UserData user;

	user.handle = handle;
	// 接続してきたマシンのＩＰアドレスを得る
	GetNetWorkIP(handle, &user.ip);

	// ユーザー配列に追加
	m_UserData.push_back(user);
}

/// <summary>
/// ユーザーデータを取り除く
/// </summary>
/// <param name="handle">取り除くユーザーのハンドル</param>
void Server::RemoveUserData(int handle)
{
	// イテレータを使って部分削除する
	for(auto itr = m_UserData.begin(); itr != m_UserData.end(); itr++)
	{
		// 削除するユーザーをハンドルから検索
		if ((*itr).handle == handle)
		{
			// 見つかったら削除して終了
			m_UserData.erase(itr);
			return;
		}
	}
}
