#pragma once
#include "../Singleton/Singleton.h"
#include "../Memory/Memory.h"

class ClientAPI;

class GameApp : public Singleton<GameApp>
{
public:
	GameApp();
	~GameApp();

	void Init();
	void Exec();

	void StartNetwork();
	void EndNetwork();

	bool IsConnected() const;

	ClientAPI& GetClientAPI() { return *m_ClientAPI; }

private:
	UniquePtr<ClientAPI> m_ClientAPI;
};