#pragma once
#include <list>
#include "NetworkCommonParam.h"


struct ClientData
{
	int handle;
	IPDATA ip;
};

class Server
{
public:
	Server();
	~Server();

public:
	void Init();
	void Update();
	void Draw();
	void Fin();

private:
	void AddUserData(int handle);		// ユーザーデータを追加
	void RemoveUserData(int handle);	// ユーザーデータを除外
	void ReceiveData();					// データ受信

private:
	std::list<ClientData> m_ClientData;
	// 受信するチャットデータ

};
