#include "NetworkManager.h"

// ポート番号を設定
// ゲームでは49152〜65535を推奨
#define PORT (50000)


NetworkManager* NetworkManager::m_Instance = nullptr;

NetworkManager::NetworkManager()
{
	m_NWHandle = 0;
	m_NWGameState = GAME_STATE_OFFLINE;
	m_NWState = NW_STATE_DISCONNECT;
	m_IPAddress = {};
}

NetworkManager::~NetworkManager()
{
	Fin();
}

void NetworkManager::Update()
{
	// 接続待ち中
	if (m_NWState == NW_STATE_WAITING_CONNECTION)
	{
		// 接続できたかチェック
		if (GetNetWorkAcceptState(m_NWHandle))
		{
			// 接続完了
			m_NWGameState = GAME_STATE_ONLINE;
			m_NWState = NW_STATE_CONNECT;
		}
	}
}

void NetworkManager::Draw()
{
	DrawFormatString(0, 20, GetColor(255, 255, 255), 
		"接続先IPアドレス：%d.%d.%d.%d", m_IPAddress.d1, m_IPAddress.d2, m_IPAddress.d3, m_IPAddress.d4);
}

void NetworkManager::Fin()
{
	// 状態が接続中以降であれば切断
	if (m_NWState >= NW_STATE_WAITING_CONNECTION)
	{
		Disconnect();
	}
}

void NetworkManager::Connect()
{
	// 指定したIPアドレスの端末に接続
	m_NWHandle = ConnectNetWork(m_IPAddress, PORT);

	// 接続待ちへ
	m_NWState = NW_STATE_WAITING_CONNECTION;
}

void NetworkManager::Disconnect()
{
	// 切断
	CloseNetWork(m_NWHandle);
	m_NWHandle = 0;
	m_NWGameState = GAME_STATE_OFFLINE;
	m_NWState = NW_STATE_DISCONNECT;
}
