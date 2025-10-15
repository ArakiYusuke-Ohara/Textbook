#include "NetworkPlayScene.h"
#include "../Player/PlayerManager.h"
#include "../Player/NetworkPlayer.h"
#include "../Network/Client.h"

NetworkPlayScene::NetworkPlayScene()
{
}

NetworkPlayScene::~NetworkPlayScene()
{
	Fin();
}

void NetworkPlayScene::Init()
{
	// クライアントクラス生成
	m_Client = MakeUnique<Client>();

	PlayerManager::CreateInstance();
	NetworkPlayer& nwPlayer = PlayerManager::GetInstance()->CreateNetworkPlayer(*m_Client);
}

void NetworkPlayScene::Step()
{
	PlayScene::Step();


}

void NetworkPlayScene::Fin()
{
	PlayScene::Fin();


}
