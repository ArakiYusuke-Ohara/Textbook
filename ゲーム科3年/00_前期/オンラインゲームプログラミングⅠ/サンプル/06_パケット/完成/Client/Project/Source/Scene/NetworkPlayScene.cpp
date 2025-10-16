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
	m_Client->Init();

	PlayerManager::CreateInstance();
	PlayerManager::GetInstance()->CreateNetworkPlayer(*m_Client);
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

}

void NetworkPlayScene::ReceivePos()
{
	// 座標データを受信
	Network::PosData data = {};
	m_Client->ReceiveData(reinterpret_cast<char*>(&data), sizeof(data));

}

