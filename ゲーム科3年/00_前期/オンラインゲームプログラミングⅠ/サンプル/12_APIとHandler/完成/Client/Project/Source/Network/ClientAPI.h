#pragma once
#include "Client.h"
#include "../Component/Transform/Transform.h"

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
	void RequestLogout(int playerID);
	void RequestTransform(int playerID, Transform transform);

	// サーバーからの受信処理
	void OnReceiveLogin();
	void OnReceiveJoin();
	void OnReceiveLogout();
	void OnReceiveAllTransform();
	void OnReceiveDead();

	void Fin();

private:
	Client m_Client;
};
