#include "PlayScene.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
	Fin();
}

void PlayScene::Init()
{
	PlayerManager::CreateInstance();
	Player& player = PlayerManager::GetInstance()->CreatePlayer();
	player.SetPos(VGet(100.0f, 100.0f, 0.0f));
}

void PlayScene::Load()
{
	PlayerManager::GetInstance()->Load();
}

void PlayScene::Start()
{
}

void PlayScene::Step()
{
	PlayerManager::GetInstance()->Step();
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
	PlayerManager::GetInstance()->Draw();
}

void PlayScene::Fin()
{
	PlayerManager::DeleteInstance();
}
