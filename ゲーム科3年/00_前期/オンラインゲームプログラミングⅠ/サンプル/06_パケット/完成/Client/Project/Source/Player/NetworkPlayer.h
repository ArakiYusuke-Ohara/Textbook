#pragma once
#include "Player.h"

class Client;

class NetworkPlayer : public Player
{
public:
	NetworkPlayer(Client& client);
	virtual ~NetworkPlayer();

	void Init() override;
	void Step() override;

	void StepOffline();
	void StepOnline();

private:
	void SendPosData();

	void ReceiveData();
	void ReceiveLogin();
	void ReceivePos();

private:
	int m_ID;
	Client& m_Client;
	Transform m_ServerTransform;
};
