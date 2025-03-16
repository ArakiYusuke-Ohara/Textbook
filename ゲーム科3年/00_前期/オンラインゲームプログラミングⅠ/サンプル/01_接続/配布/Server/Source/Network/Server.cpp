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

}

void Server::Update()
{

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

}

/// <summary>
/// ユーザーデータを取り除く
/// </summary>
/// <param name="handle">取り除くユーザーのハンドル</param>
void Server::RemoveUserData(int handle)
{

}
