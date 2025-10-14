#pragma once
#include "Player.h"

class Client;

class NetworkPlayer : public Player
{
public:
	NetworkPlayer();
	virtual ~NetworkPlayer();

	void Init() override;
	void Step() override;

	void StepOffline();
	void StepOnline();

private:
	UniquePtr<Client> m_Client;
	Transform m_ServerTransform;
};
