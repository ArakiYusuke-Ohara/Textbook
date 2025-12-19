#pragma once
#include "Client.h"

class ClientAPI
{
public:
	// コピー禁止
	ClientAPI(const ClientAPI&) = delete;
	ClientAPI& operator=(const ClientAPI&) = delete;

	// ムーブ禁止
	ClientAPI(ClientAPI&&) = delete;
	ClientAPI& operator=(ClientAPI&&) = delete;

	ClientAPI() = default;
	~ClientAPI();

	void Connect();
	void Step();
	void Draw();

	bool IsConnected() const { return m_Client.IsConnected(); }

	// サーバーへのリクエスト処理
	void RequestLogin();
	void RequestJoin();
	void RequestLogout();

	// サーバーからのレスポンス処理
	void ReceiveLogin();
	void ReceiveJoin();
	void ReceiveLogout();
	void ReceiveAllTransform();
	void ReceiveDie();

	void Fin();

private:
	Client m_Client;
};
