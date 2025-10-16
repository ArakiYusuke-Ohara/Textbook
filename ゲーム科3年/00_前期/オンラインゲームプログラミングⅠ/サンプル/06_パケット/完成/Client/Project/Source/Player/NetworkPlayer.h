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

private:
	Client& m_Client;
	Transform m_ServerTransform;
};
