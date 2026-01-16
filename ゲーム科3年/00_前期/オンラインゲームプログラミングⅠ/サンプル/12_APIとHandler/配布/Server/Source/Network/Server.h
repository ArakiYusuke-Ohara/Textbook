#pragma once
#include <list>
#include <string>
#include "NetworkCommonParam.h"

class Player;

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
	void ReceiveData();					// データ受信
	void SyncTransform(int handle);
	void CheckCollision();
};
