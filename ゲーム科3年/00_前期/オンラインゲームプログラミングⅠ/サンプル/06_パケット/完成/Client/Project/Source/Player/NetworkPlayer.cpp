#include "NetworkPlayer.h"
#include "../Network/Client.h"
#include "../MyMath/MyMath.h"
#include "../Network/NetworkUtility.h"

// これだけ動いたらサーバーに送信する
constexpr float POS_THRESHOLD = 0.05f;
constexpr float SCALE_THRESHOLD = 0.01f;
constexpr float ROT_THRESHOLD = 0.01f;


NetworkPlayer::NetworkPlayer(Client& client) : Player()
, m_Client(client)
{
	m_ID = -1;
}

NetworkPlayer::~NetworkPlayer() = default;

void NetworkPlayer::Init()
{
	Player::Init();

	m_Client.Connect();
}

void NetworkPlayer::Step()
{
	m_Client.Step();

	// 状態毎の更新
	Client::State state = m_Client.GetState();
	switch (state)
	{
		case Client::State::OFFLINE: StepOffline(); break;
		case Client::State::ONLINE: StepOnline(); break;
	}

	// サーバーからの受信処理
	ReceiveData();
}

void NetworkPlayer::StepOffline()
{
	// とくにやることなし
}

void NetworkPlayer::StepOnline()
{
	Transform oldTransform = m_Transform;

	// 移動とか
	Player::Step();

	// 移動したらサーバーに座標を送信
	float dist = MyMath::GetDistance(m_Transform.GetPos(), oldTransform.GetPos());
	if (dist >= POS_THRESHOLD)
	{
		SendPosData();
	}

	// 拡縮したらサーバーにスケールを送信
	dist = MyMath::GetDistance(m_Transform.GetScale(), oldTransform.GetScale());
	if (dist >= SCALE_THRESHOLD)
	{
	}

	// 回転したらサーバーに回転値を送信
	dist = MyMath::GetDistance(m_Transform.GetRot(), oldTransform.GetRot());
	if (dist >= ROT_THRESHOLD)
	{
	}
}

void NetworkPlayer::SendPosData()
{
	VECTOR pos = m_Transform.GetPos();
	Network::PosData data;
	data.playerID = m_ID;
	data.x = pos.x;
	data.y = pos.y;
	data.z = pos.z;

	std::vector<uint8_t> buf = Network::NetworkUtility::MakePosData(data);

	NetWorkSend(m_Client.GetServerHandle(), reinterpret_cast<const char*>(buf.data()), (int)buf.size());
}

void NetworkPlayer::ReceiveData()
{
	if (m_Client.CheckReceive())
	{
		// ヘッダーのみを受信
		Network::PacketHeader header = {};
		m_Client.ReceiveData(reinterpret_cast<char*>(&header), sizeof(header));

		switch (header.packet)
		{
			case Network::Packet::LOGIN: ReceiveLogin(); break;
			case Network::Packet::POS: ReceivePos(); break;
		}
	}

}

void NetworkPlayer::ReceiveLogin()
{

}

void NetworkPlayer::ReceivePos()
{
}

