#pragma once
#include "../Singleton/Singleton.h"
#include "../Memory/Memory.h"
#include <vector>

class Player;
class NetworkPlayer;
class Client;

class PlayerManager : public Singleton<PlayerManager>
{
public:
	PlayerManager();
	virtual ~PlayerManager();

	void Load();
	void Start();
	void Step();
	void Draw();

	Player& CreatePlayer();
	NetworkPlayer& CreateNetworkPlayer(Client& client);
	void JoinNetworkPlayer(Client& client, int id);


private:
	std::vector<UniquePtr<Player>> m_Players;
};
