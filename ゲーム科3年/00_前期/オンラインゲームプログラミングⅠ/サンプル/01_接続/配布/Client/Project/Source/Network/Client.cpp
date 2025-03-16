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

}

/// <summary>
/// サーバーから切断する
/// </summary>
void Client::Disconnect()
{

}
