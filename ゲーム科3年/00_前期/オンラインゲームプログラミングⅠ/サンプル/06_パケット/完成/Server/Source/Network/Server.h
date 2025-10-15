#pragma once
#include <list>
#include <string>
#include "NetworkCommonParam.h"


struct ClientData
{
	int handle;
	IPDATA ip;
};

struct NetworkPlayerData
{
	ClientData client;
	VECTOR pos;
	VECTOR scale;
	VECTOR rot;
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
	void SendLoginData();

private:
	std::list<NetworkPlayerData> m_NetworkPlayerData;
};
