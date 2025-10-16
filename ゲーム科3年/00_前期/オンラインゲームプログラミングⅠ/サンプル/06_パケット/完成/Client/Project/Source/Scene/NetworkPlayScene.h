#pragma once
#include "PlayScene.h"
#include "../Memory/Memory.h"

class Client;

class NetworkPlayScene : public PlayScene
{
public:
	NetworkPlayScene();
	virtual ~NetworkPlayScene();

public:
	void Init()override;
	void Step()override;
	void Fin()override;

private:
	void ReceiveData();
	void ReceiveLogin();
	void ReceivePos();

private:
	UniquePtr<Client> m_Client;
};
