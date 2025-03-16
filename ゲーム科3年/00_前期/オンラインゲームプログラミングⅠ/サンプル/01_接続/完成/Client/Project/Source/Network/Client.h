#pragma once
#include "DxLib.h"

// ゲームの状態
enum NetworkGameState
{
	GAME_STATE_OFFLINE,	// オフライン中
	GAME_STATE_ONLINE,	// オンライン中
};

// 通信の状態
enum NetworkState
{
	NW_STATE_DISCONNECT,			// 切断している
	NW_STATE_WAITING_CONNECTION,	// 接続中
	NW_STATE_CONNECT,				// 接続している
};

class Client
{
public:
	Client();
	~Client();

public:
	void Init();
	void Update();
	void Draw();
	void Fin();

	void Connect();
	void Disconnect();

public:
	void SetIPAddress(IPDATA address) { m_IPAddress = address; }

	bool IsConnect() const { return m_IsConnect; }
	NetworkGameState GetNetworkGameState() const { return m_NWGameState; }
	NetworkState GetNetworkState() const { return m_NWState; }


private:
	bool m_IsConnect;
	int m_NWHandle;
	NetworkGameState m_NWGameState;
	NetworkState m_NWState;
	IPDATA m_IPAddress;
};

