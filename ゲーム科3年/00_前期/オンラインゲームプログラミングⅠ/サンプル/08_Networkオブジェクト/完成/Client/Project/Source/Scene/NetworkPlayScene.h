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
	void Load()override;
	void Step()override;
	void Draw()override;
	void Fin()override;

private:
	void ReceiveData();

private:
	UniquePtr<Client> m_Client;
};
