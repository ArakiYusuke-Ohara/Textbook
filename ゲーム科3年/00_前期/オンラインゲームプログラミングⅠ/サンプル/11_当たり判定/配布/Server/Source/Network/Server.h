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
	bool ReceiveData();					// データ受信
	void SendLoginData(const Player& loginPlayer);
	void SendJoinData(const Player& joinPlayer);
	void SendLogoutData(int id);
	void SendAllTransformData();
	void SyncPos(int handle);
	void SyncRot(int handle);
	void SyncScale(int handle);
	void SyncTransform(int handle);
	void CheckCollision();
};
