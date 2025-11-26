#pragma once
#include "../Singleton/Singleton.h"
#include "../Memory/Memory.h"
#include <vector>

class Player;

class PlayerManager : public Singleton<PlayerManager>
{
public:
	PlayerManager() = default;
	~PlayerManager() = default;

	Player& CreatePlayer();

private:
	std::vector<SharedPtr<Player>> m_Players;
};

