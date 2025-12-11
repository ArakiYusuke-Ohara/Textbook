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

	// 機能
	Player& CreatePlayer();

	// ネットワーク関係
	NetworkPlayer& CreateNetworkPlayer(const Client* client, int id, bool isSelf);
	void Login(const Client* client, Network::LoginData data);
	void Join(Network::JoinData data);
	void Logout(Network::LogoutData data);
	void SyncTransform(Network::AllTransformData data);
	void DiePlayer(int playerID);

private:
	std::list<UniquePtr<Player>> m_Players;
};
