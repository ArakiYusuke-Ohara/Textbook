#include "NetworkPlayScene.h"
#include "../Player/PlayerManager.h"
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
	// サーバーに接続
	m_Client->Connect();

	// プレイヤー管理生成
	PlayerManager::CreateInstance();
}

void NetworkPlayScene::Load()
{
	// どのプレイヤーが参加するかわからないのでロードできない
	// ロードは参加時に行う
}

void NetworkPlayScene::Step()
{
	PlayScene::Step();

	// クライアントステップ
	m_Client->Step();

	// 常に受信がないか見張る
	ReceiveData();
}

void NetworkPlayScene::Draw()
{
	PlayScene::Draw();

	if (m_Client) m_Client->Draw();
}

void NetworkPlayScene::Fin()
{
	PlayScene::Fin();
}

void NetworkPlayScene::ReceiveData()
{
	// TODO:サーバーからの受信処理を書く

}

