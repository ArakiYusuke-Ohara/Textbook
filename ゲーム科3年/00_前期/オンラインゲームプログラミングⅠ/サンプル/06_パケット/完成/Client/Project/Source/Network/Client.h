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

	void Step();
	void Draw();
	void Fin();

	void Connect();
	void SendData(const void* data, unsigned int size);
	void ReceveData(void* buffer, unsigned int size);
	void Disconnect();

	// 通信の状態
	enum State
	{
		OFFLINE,	// オフライン
		WAIT,		// 接続待ち
		ONLINE,		// オンライン
	};

	State GetState() const { return m_State; }
	void SetIPAddress(IPDATA address) { m_IPAddress = address; }

private:
	void UpdateWaiting();
	void UpdateOnline();

	int m_ServerHandle;
	State m_State;
	IPDATA m_IPAddress;
};

