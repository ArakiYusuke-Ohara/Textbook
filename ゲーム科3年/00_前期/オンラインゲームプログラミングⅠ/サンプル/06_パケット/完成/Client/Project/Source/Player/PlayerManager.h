#pragma once
#include "../Singleton/Singleton.h"
#include "../Memory/Memory.h"
#include <vector>

class Player;
class NetworkPlayer;

class PlayerManager : public Singleton<PlayerManager>
{
public:
	PlayerManager();
	virtual ~PlayerManager();

	void Load();
	void Step();
	void Draw();

	Player& CreatePlayer();
	NetworkPlayer& CreateNetworkPlayer();


private:
	std::vector<UniquePtr<Player>> m_Players;
};
