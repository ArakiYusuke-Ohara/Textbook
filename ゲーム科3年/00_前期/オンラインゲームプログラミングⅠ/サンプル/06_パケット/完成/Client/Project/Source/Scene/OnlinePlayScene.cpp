#include "OnlinePlayScene.h"
#include "../Player/PlayerManager.h"

OnlinePlayScene::OnlinePlayScene()
{
}

OnlinePlayScene::~OnlinePlayScene()
{
	Fin();
}

void OnlinePlayScene::Init()
{
	PlayerManager::CreateInstance();	
}

void OnlinePlayScene::Load()
{
}

void OnlinePlayScene::Start()
{
}

void OnlinePlayScene::Step()
{
}

void OnlinePlayScene::Update()
{
}

void OnlinePlayScene::Draw()
{
}

void OnlinePlayScene::Fin()
{
}
