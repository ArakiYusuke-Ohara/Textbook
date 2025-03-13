#include "NetworkManager.h"
#include "NetworkCommonParam.h"

NetworkManager* NetworkManager::m_Instance = nullptr;

NetworkManager::NetworkManager()
{
	m_UserData = {};
}

NetworkManager::~NetworkManager()
{
	Fin();
}

void NetworkManager::Init()
{
	// 接続してくるのを待つ状態にする
	PreparationListenNetWork(PORT_NUMBER);
}

void NetworkManager::Update()
{
	// 新しい接続があったらそのネットワークハンドルを得る
	int acceptHandle = GetNewAcceptNetWork();

	// 新しい接続があった
	if (acceptHandle != -1)
	{
		AddUserData(acceptHandle);
	}

}

void NetworkManager::Draw()
{
	int count = 0;
	for (UserData user : m_UserData)
	{
		DrawFormatString(0, count * 20, GetColor(255, 255, 255), "User%02d : %d.%d.%d.%d", count, user.ip.d1, user.ip.d2, user.ip.d3, user.ip.d4);
		count++;
	}
}

void NetworkManager::Fin()
{
}

void NetworkManager::AddUserData(int handle)
{
	UserData user;

	user.handle = handle;
	// 接続してきたマシンのＩＰアドレスを得る
	GetNetWorkIP(handle, &user.ip);

	// ユーザー配列に追加
	m_UserData.push_back(user);
}
