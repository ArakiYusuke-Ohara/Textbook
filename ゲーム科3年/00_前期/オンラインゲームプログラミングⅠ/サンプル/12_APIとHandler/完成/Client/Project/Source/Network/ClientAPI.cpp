#include "ClientAPI.h"
#include "NetworkUtility.h"
#include "../Player/PlayerManager.h"

using namespace Network;

ClientAPI::~ClientAPI()
{
	Fin();
}

void ClientAPI::Connect()
{
	m_Client.Connect();
}

void ClientAPI::Step()
{
	m_Client.Step();

	if (m_Client.CheckReceive())
	{
		// ヘッダーのみを受信
		Network::PacketHeader header = {};
		m_Client.ReceiveData(reinterpret_cast<char*>(&header), sizeof(header));

		switch (header.type)
		{
			case Network::PacketType::LOGIN:			ReceiveLogin(); break;
			case Network::PacketType::JOIN:				ReceiveJoin(); break;
			case Network::PacketType::LOGOUT:			ReceiveLogout(); break;
			case Network::PacketType::ALL_TRANSFORM:	ReceiveAllTransform(); break;
			case Network::PacketType::DIE:				ReceiveDie(); break;
		}
	}
}

void ClientAPI::Draw()
{
	m_Client.Draw();
}

void ClientAPI::RequestLogin()
{
	RequestLoginData data = {};
	auto packet = MakePacket<RequestLoginData>(PacketType::LOGIN, data);

	m_Client.SendData(packet.data(), (unsigned int)packet.size());
}

void ClientAPI::RequestJoin()
{
}

void ClientAPI::RequestLogout()
{
}

void ClientAPI::ReceiveLogin()
{
	// ログインデータを受信
	Network::ResponseLoginData data = {};
	m_Client.ReceiveData(reinterpret_cast<char*>(&data), sizeof(data));

	// ログイン処理
	PlayerManager::GetInstance()->Login(data);
}

void ClientAPI::ReceiveJoin()
{
	// 参加データを受信
	Network::JoinData data = {};
	m_Client.ReceiveData(reinterpret_cast<char*>(&data), sizeof(data));

	// プレイヤー参加処理
	PlayerManager::GetInstance()->Join(data);
}

void ClientAPI::ReceiveLogout()
{
	// ログアウトデータを受信
	Network::LogoutData data = {};
	m_Client.ReceiveData(reinterpret_cast<char*>(&data), sizeof(data));

	// ログアウト
	PlayerManager::GetInstance()->Logout(data);
}

void ClientAPI::ReceiveAllTransform()
{
	// 座標データを受信
	Network::AllTransformData data = {};
	m_Client.ReceiveData(reinterpret_cast<char*>(&data), sizeof(data));

	// 座標同期
	PlayerManager::GetInstance()->SyncTransform(data);

}

void ClientAPI::ReceiveDie()
{
	// 死亡データを受信
	Network::DieData data = {};
	m_Client.ReceiveData(reinterpret_cast<char*>(&data), sizeof(data));

	// 死亡させる
	PlayerManager::GetInstance()->DiePlayer(data.playerID);
}

void ClientAPI::Fin()
{
	m_Client.Fin();
}
