#include "DxLib.h"
#include "Client.h"
#include "NetworkCommonParam.h"

Client::Client()
{
	m_NWHandle = 0;
	m_NWGameState = GAME_STATE_OFFLINE;
	m_NWState = NW_STATE_DISCONNECT;
	m_IPAddress = {};
}

Client::~Client()
{
	Fin();
}

void Client::Init()
{
}

void Client::Update()
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

void Client::Draw()
{
	DrawFormatString(0, 20, GetColor(255, 255, 255), "接続先IPアドレス：%d.%d.%d.%d", m_IPAddress.d1, m_IPAddress.d2, m_IPAddress.d3, m_IPAddress.d4);
}

void Client::Fin()
{
	// 状態が接続中以降であれば切断
	if (m_NWState >= NW_STATE_WAITING_CONNECTION)
	{
		Disconnect();
	}
}

/// <summary>
/// サーバーに接続する
/// </summary>
void Client::Connect()
{
	// 指定したIPアドレスの端末に接続
	m_NWHandle = ConnectNetWork(m_IPAddress, PORT_NUMBER);

	// ハンドルが-1なら接続できてない
	if (m_NWHandle != -1)
	{
		// 接続待ちへ
		m_NWState = NW_STATE_WAITING_CONNECTION;
	}
}

/// <summary>
/// サーバーから切断する
/// </summary>
void Client::Disconnect()
{
	// 切断
	CloseNetWork(m_NWHandle);
	m_NWHandle = 0;
	m_NWGameState = GAME_STATE_OFFLINE;
	m_NWState = NW_STATE_DISCONNECT;

}
