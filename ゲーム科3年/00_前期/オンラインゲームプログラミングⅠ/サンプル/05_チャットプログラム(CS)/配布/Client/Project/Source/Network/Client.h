#pragma once
#include "DxLib.h"
#include "NetworkCommonParam.h"
#include <list>

class InputString;

// 通信の状態
enum NetworkState
{
	NW_STATE_NANE_INPUT,			// 名前入力
	NW_STATE_WAITING_CONNECTION,	// 接続待ち
	NW_STATE_MESSAGE_INPUT,			// メッセージ入力
};

class Client
{
public:
	Client();
	~Client();

	void Init();
	void Update();
	void Draw();
	void Fin();

	void Connect();
	void Disconnect();

	void SetIPAddress(IPDATA address) { m_IPAddress = address; }

private:
	void UpdateNameInput();
	void UpdateWaitingConnection();
	void UpdateMessageInput();
	void ReceiveData();
	void DrawChat();

private:
	int m_ServerHandle;
	NetworkState m_NWState;
	IPDATA m_IPAddress;
	InputString* m_UserNameInput;
	InputString* m_MessageInput;
	// 送信するチャットデータ
	ChatData m_SendChatData;
	// サーバーから送られてきたチャットデータ
	std::list<ChatData> m_ServerChatData;
};

