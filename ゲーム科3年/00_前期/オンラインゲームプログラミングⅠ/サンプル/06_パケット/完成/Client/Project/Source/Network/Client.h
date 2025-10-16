#pragma once
#include "DxLib.h"
#include "NetworkCommonParam.h"
#include <list>

class InputString;

class Client
{
public:

	Client();
	~Client();

	void Init();
	void Step();
	void Draw();
	void Fin();

	void Connect();
	void SendData(const void* data, unsigned int size);
	bool CheckReceive();
	void ReceiveData(void* buffer, unsigned int size);
	void Disconnect();

	// 通信の状態
	enum State
	{
		OFFLINE,	// オフライン
		WAIT,		// 接続待ち
		ONLINE,		// オンライン
	};

	State GetState() const { return m_State; }
	int GetServerHandle() const { return m_ServerHandle; }
	void SetIPAddress(IPDATA address) { m_IPAddress = address; }

private:
	void UpdateWaiting();
	void StepOnline();

	int m_ServerHandle;
	State m_State;
	IPDATA m_IPAddress;
};

