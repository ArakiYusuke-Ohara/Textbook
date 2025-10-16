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
	PlayerManager::CreateInstance();
	PlayerManager::GetInstance()->CreateNetworkPlayer(*m_Client);

	// クライアントクラス生成
	m_Client = MakeUnique<Client>();
	// サーバーに接続
	m_Client->Connect();
}

void NetworkPlayScene::Step()
{
	PlayScene::Step();

	ReceiveData();
}

void NetworkPlayScene::Fin()
{
	PlayScene::Fin();


}

void NetworkPlayScene::ReceiveData()
{
	if (m_Client->CheckReceive())
	{
		// ヘッダーのみを受信
		Network::PacketHeader header = {};
		m_Client->ReceiveData(reinterpret_cast<char*>(&header), sizeof(header));

		switch (header.packet)
		{
			case Network::Packet::LOGIN: ReceiveLogin(); break;
			case Network::Packet::POS: ReceivePos(); break;
		}
	}

}

void NetworkPlayScene::ReceiveLogin()
{
	// ログインデータを受信
	Network::LoginData data = {};
	m_Client->ReceiveData(reinterpret_cast<char*>(&data), sizeof(data));

	// プレイヤー追加
	PlayerManager::GetInstance()->JoinNetworkPlayer(*m_Client, data.playerID);
}

void NetworkPlayScene::ReceivePos()
{
	// 座標データを受信
	Network::PosData data = {};
	m_Client->ReceiveData(reinterpret_cast<char*>(&data), sizeof(data));

}

