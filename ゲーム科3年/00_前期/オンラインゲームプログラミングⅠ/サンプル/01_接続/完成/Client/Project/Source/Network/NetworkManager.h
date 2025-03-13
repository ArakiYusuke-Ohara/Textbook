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

class NetworkManager
{
public:
	NetworkManager();
	~NetworkManager();

public:
	static void CreateInstance() { if (!m_Instance) m_Instance = new NetworkManager; }
	static NetworkManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

public:
	void Update();
	void Draw();
	void Fin();

public:
	void SetIPAddress(IPDATA address) { m_IPAddress = address; }

	NetworkGameState GetNetworkGameState() const { return m_NWGameState; }
	NetworkState GetNetworkState() const { return m_NWState; }

public:
	void Connect();		// 接続
	void Disconnect();	// 切断

private:
	static NetworkManager* m_Instance;
	int m_NWHandle;
	NetworkGameState m_NWGameState;
	NetworkState m_NWState;
	IPDATA m_IPAddress;
};
