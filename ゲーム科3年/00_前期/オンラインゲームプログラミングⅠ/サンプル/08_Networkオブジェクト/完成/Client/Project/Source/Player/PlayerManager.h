#pragma once
#include "../Singleton/Singleton.h"
#include "../Memory/Memory.h"
#include "../Network/NetworkCommonParam.h"
#include <list>

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

	// ‹@”\
	Player& CreatePlayer();

private:
	std::list<UniquePtr<Player>> m_Players;
};
