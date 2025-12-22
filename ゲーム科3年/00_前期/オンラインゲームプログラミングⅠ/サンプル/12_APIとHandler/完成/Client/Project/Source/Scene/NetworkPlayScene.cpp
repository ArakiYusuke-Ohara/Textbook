#include "NetworkPlayScene.h"
#include "../Player/PlayerManager.h"
#include "../GameApp/GameApp.h"
#include "../Network/ClientAPI.h"

NetworkPlayScene::~NetworkPlayScene()
{
	Fin();
}

void NetworkPlayScene::Init()
{
	// ログイン
	ClientAPI::RequestLogin();

	// プレイヤー管理生成
	PlayerManager::CreateInstance();
}

void NetworkPlayScene::Load()
{
	// どのプレイヤーが参加するかわからないのでロードできない
	// ロードは参加時に行う
}

void NetworkPlayScene::Fin()
{
	PlayScene::Fin();

	// ネットワーク終了
	ClientAPI::Disconnect();
}
