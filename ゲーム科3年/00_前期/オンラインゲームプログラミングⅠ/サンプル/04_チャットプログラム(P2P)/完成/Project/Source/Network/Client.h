#pragma once
#include "DxLib.h"
#include "NetworkCommonParam.h"
#include "../Memory/Memory.h"
#include <vector>

class InputString;

// 通信の状態
enum NetworkState
{
	NW_STATE_NONE,
	NW_STATE_INPUT_NAME,			// ユーザー名入力中
	NW_STATE_WAITING,				// 接続待ち
	NW_STATE_INPUT_MESSAGE,			// メッセージ入力中
};

class Client
{
public:
	Client();
	virtual ~Client();

public:
	void Init();
	void Update();
	void Draw();
	void Fin();

private:
	// ホスト/クライアント共通処理
	void UpdateInputName();
	void UpdateInputMessage();
	void ReceiveData();
	void DrawChat();
	void Connect();
	void Disconnect();

private:
	// ホスト/クライアントで別々の処理
	virtual void StartNetwork();
	virtual void UpdateWaiting();
	virtual void DrawWaiting();

public:
	void SetIPAddress(IPDATA address) { m_IPAddress = address; }

	NetworkState GetNetworkState() const { return m_NWState; }

protected:
	int m_PartnerHandle;	// （Host:Clientのハンドル / Cilent:Hostのハンドル）
	ChatData m_SendChatData;
	UniquePtr<InputString> m_MessageInput;
	NetworkState m_NWState;

private:
	IPDATA m_IPAddress;
	UniquePtr<InputString> m_NameInput;
	std::vector<ChatData> m_ChatData;
};
