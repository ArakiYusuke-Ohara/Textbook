#include "NetworkPlayScene.h"
#include "../Player/PlayerManager.h"
#include "../Player/NetworkPlayer.h"

NetworkPlayScene::NetworkPlayScene()
{
}

NetworkPlayScene::~NetworkPlayScene()
{
	Fin();
}

void NetworkPlayScene::Init()
{
	PlayerManager::CreateInstance();
	NetworkPlayer& nwPlayer = PlayerManager::GetInstance()->CreateNetworkPlayer();
	nwPlayer.SetPos(VGet(100.0f, 100.0f, 0.0f));
}

void NetworkPlayScene::Load()
{
	PlayerManager::GetInstance()->Load();
}

void NetworkPlayScene::Start()
{
}

void NetworkPlayScene::Step()
{
	PlayerManager::GetInstance()->Step();
}

void NetworkPlayScene::Update()
{
}

void NetworkPlayScene::Draw()
{
}

void NetworkPlayScene::Fin()
{
}
