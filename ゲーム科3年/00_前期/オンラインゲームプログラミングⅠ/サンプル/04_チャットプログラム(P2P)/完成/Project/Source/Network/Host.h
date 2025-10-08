#pragma once
#include "Client.h"


class Host : public Client
{
public:
	Host();
	virtual ~Host();

private:
	void SetUserData(int handle);

private:
	void StartNetwork() override;
	bool WaitingConnection() override;

private:
	ClientData m_MatchingClientData;
};