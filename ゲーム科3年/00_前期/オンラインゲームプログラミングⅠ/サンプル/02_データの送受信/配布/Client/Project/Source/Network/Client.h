#pragma once
#include "DxLib.h"
#include "NetworkCommonParam.h"

class InputString;

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

private:
	void UpdateDisconnect();
	void UpdateWaitingConnection();
	void UpdateConnect();

public:
	void SetIPAddress(IPDATA address) { m_IPAddress = address; }

	NetworkState GetNetworkState() const { return m_NWState; }

private:
	int m_ServerHandle;
	NetworkState m_NWState;
	IPDATA m_IPAddress;
	InputString* m_UserNameInput;
	InputString* m_MessageInput;
	// 送信するチャットデータ
};

