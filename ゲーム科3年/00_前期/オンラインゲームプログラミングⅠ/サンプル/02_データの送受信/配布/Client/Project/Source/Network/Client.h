#pragma once
#include "DxLib.h"
#include "NetworkCommonParam.h"

class InputString;

// ’ÊM‚Ìó‘Ô
enum NetworkState
{
	NW_STATE_DISCONNECT,			// Ø’f‚µ‚Ä‚¢‚é
	NW_STATE_WAITING_CONNECTION,	// Ú‘±’†
	NW_STATE_CONNECT,				// Ú‘±‚µ‚Ä‚¢‚é
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
	ClientChatData m_ChatData;
};

