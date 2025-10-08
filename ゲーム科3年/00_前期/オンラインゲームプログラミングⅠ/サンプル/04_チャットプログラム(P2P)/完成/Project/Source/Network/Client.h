#pragma once
#include "DxLib.h"
#include "NetworkCommonParam.h"
#include <vector>

class InputString;

struct ClientData
{
	int handle;
	IPDATA ip;
};

// 通信の状態
enum NetworkState
{
	NW_STATE_SELECT_HOST,			// ホストかどうか選択中
	NW_STATE_INPUT_USER_NAME,			// 切断している
	NW_STATE_WAITING_MATCHING,		// マッチング中
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
	void SetUserData(int handle);
	void UpdateSelectHost();
	void UpdateDisconnect();
	void UpdateWaitingMatching();
	void UpdateWaitingConnection();
	void UpdateConnect();
	void ReceiveData();
	void DrawChat();

public:
	void SetIPAddress(IPDATA address) { m_IPAddress = address; }

	NetworkState GetNetworkState() const { return m_NWState; }

private:
	// ホストかクライアントか
	enum Mode
	{
		MODE_NONE,
		MODE_HOST,
		MODE_CLIENT,
	};

private:
	int m_HostHandle;
	Mode m_Mode;
	ClientData m_MatchingClientData;
	NetworkState m_NWState;
	IPDATA m_IPAddress;
	InputString* m_UserNameInput;
	InputString* m_MessageInput;
	ChatData m_SendChatData;
	std::vector<ChatData> m_ChatData;
};
