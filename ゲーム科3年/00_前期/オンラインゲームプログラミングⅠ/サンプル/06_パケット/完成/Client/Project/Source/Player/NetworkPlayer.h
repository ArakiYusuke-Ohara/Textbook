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

	void UpdateOffline();
	void UpdateOnline();

private:
	UniquePtr<Client> m_Client;
};
