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
			case Network::PacketType::LOGIN:			OnReceiveLogin(); break;
			case Network::PacketType::JOIN:				OnReceiveJoin(); break;
			case Network::PacketType::LOGOUT:			OnReceiveLogout(); break;
			case Network::PacketType::ALL_TRANSFORM:	OnReceiveAllTransform(); break;
			case Network::PacketType::DIE:				OnReceiveDead(); break;
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

void ClientAPI::RequestLogout(int playerID)
{
	LogoutData data = {};
	data.playerID = playerID;

	auto packet = MakePacket<LogoutData>(PacketType::LOGOUT, data);
	m_Client.SendData(packet.data(), (unsigned int)packet.size());
}

void ClientAPI::RequestTransform(int playerID, Transform transform)
{
	RequestTransformData data = {};

	data.playerID = playerID;
	data.pos = transform.GetPosition();
	data.rot = transform.GetRotation();
	data.scale = transform.GetScale();

	std::vector<uint8_t> buf = MakePacket<RequestTransformData>(PacketType::TRANSFORM, data);
	m_Client.SendData(buf.data(), (unsigned int)buf.size());
}

void ClientAPI::OnReceiveLogin()
{
	// ログインデータを受信
	Network::ResponseLoginData data = {};
	m_Client.ReceiveData(reinterpret_cast<char*>(&data), sizeof(data));

	// ログイン処理
	PlayerManager::GetInstance()->Login(data);
}

void ClientAPI::OnReceiveJoin()
{
	// 参加データを受信
	Network::JoinData data = {};
	m_Client.ReceiveData(reinterpret_cast<char*>(&data), sizeof(data));

	// プレイヤー参加処理
	PlayerManager::GetInstance()->Join(data);
}

void ClientAPI::OnReceiveLogout()
{
	// ログアウトデータを受信
	Network::LogoutData data = {};
	m_Client.ReceiveData(reinterpret_cast<char*>(&data), sizeof(data));

	// ログアウト
	PlayerManager::GetInstance()->Logout(data);
}

void ClientAPI::OnReceiveAllTransform()
{
	// 座標データを受信
	Network::ResponseTransformData data = {};
	m_Client.ReceiveData(reinterpret_cast<char*>(&data), sizeof(data));

	// 座標同期
	PlayerManager::GetInstance()->SyncServerTransform(data);

}

void ClientAPI::OnReceiveDead()
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
