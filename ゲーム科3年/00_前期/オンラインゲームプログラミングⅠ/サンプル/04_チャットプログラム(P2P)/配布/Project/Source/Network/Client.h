#pragma once
#include "DxLib.h"
#include "NetworkCommonParam.h"
#include "../Memory/Memory.h"
#include <vector>

class InputString;

class Client
{
public:
	Client();
	virtual ~Client();

	void Init();
	void Update();
	void Draw();
	void Fin();

	void SetIPAddress(IPDATA address) { m_IPAddress = address; }

private:
	// ホスト/クライアント共通処理
	void UpdateInputName();
	void UpdateInputMessage();
	void ReceiveData();
	void DrawChat();
	void Connect();
	void Disconnect();

	// ホスト/クライアントで別々の処理
	virtual void StartNetwork();
	virtual void UpdateWaiting();
	virtual void DrawWaiting();


protected:
	// 状態
	enum State
	{
		NONE,
		INPUT_NAME,			// ユーザー名入力中
		WAITING,				// 接続待ち
		INPUT_MESSAGE,			// メッセージ入力中
	};

protected:
	int m_PartnerHandle;	// （Host:Clientのハンドル / Cilent:Hostのハンドル）
	ChatData m_SendChatData;
	UniquePtr<InputString> m_NameInput;
	UniquePtr<InputString> m_MessageInput;
	State m_State;
	IPDATA m_IPAddress;
	std::vector<ChatData> m_ChatData;
};
