#include "NetworkPlayer.h"
#include "../Network/Client.h"
#include "../MyMath/MyMath.h"
#include "../Network/NetworkUtility.h"
#include "../Component/Renderer/Splite.h"

using namespace Network;

// これだけ動いたらサーバーに送信する
constexpr float POS_THRESHOLD = 1.0f;
constexpr float SCALE_THRESHOLD = 0.005f;
constexpr float ROT_THRESHOLD = 0.005f;

NetworkPlayer::NetworkPlayer(int id, bool isSelf) : Player()
, m_IsSelf(isSelf)
, m_ID(id)
{
	// サーバー座標を使用する
	m_UseServerTransform = true;
}

NetworkPlayer::NetworkPlayer(const Client* client, int id, bool isSelf) : Player()
, m_IsSelf(isSelf)
, m_ID(id)
, m_Client(client)
{
	// サーバー座標を使用する
	m_UseServerTransform = true;
}

NetworkPlayer::~NetworkPlayer() = default;

void NetworkPlayer::Step()
{
	// 自分自身しかステップしない
	if (!m_IsSelf) return;

	// 状態毎の更新
	Client::State state = m_Client->GetState();
	switch (state)
	{
		case Client::State::OFFLINE: StepOffline(); break;
		case Client::State::ONLINE: StepOnline(); break;
	}
}

void NetworkPlayer::StepOffline()
{
	// とくにやることなし
}

/// <summary>
/// 接続中のステップ
/// </summary>
void NetworkPlayer::StepOnline()
{
	// 移動とか
	Player::Step();

	// 動いたかどうか
	bool isMove = false;

	// 移動したらサーバーに座標を送信
	float dist = MyMath::GetDistance(m_Transform.GetPosition(), m_ServerTransform.GetPosition());
	if (dist >= POS_THRESHOLD)
	{
		isMove = true;
	}

	// 回転したらサーバーに回転値を送信
	dist = MyMath::GetDistance(m_Transform.GetRotation(), m_ServerTransform.GetRotation());
	if (dist >= ROT_THRESHOLD)
	{
		isMove = true;
	}

	// 拡縮したらサーバーにスケールを送信
	dist = MyMath::GetDistance(m_Transform.GetScale(), m_ServerTransform.GetScale());
	if (dist >= SCALE_THRESHOLD)
	{
		isMove = true;
	}

	// 動いたらトランスフォームを送信
	if (isMove)
	{
		SendTransformData();
	}
}

/// <summary>
/// 座標をサーバーに送信
/// </summary>
void NetworkPlayer::SendPosData()
{
	VECTOR pos = m_Transform.GetPosition();
	PosData data;
	data.playerID = m_ID;
	data.pos = pos;

	std::vector<uint8_t> buf = MakePacket<PosData>(PacketType::POS, data);
	m_Client->SendData(buf.data(), (unsigned int)buf.size());
}

void NetworkPlayer::SendRotData()
{
	VECTOR rot = m_Transform.GetRotation();
	RotData data;
	data.playerID = m_ID;
	data.rot = rot;

	std::vector<uint8_t> buf = MakePacket<RotData>(PacketType::ROT, data);
	m_Client->SendData(buf.data(), (unsigned int)buf.size());
}

void NetworkPlayer::SendScaleData()
{
	ScaleData data;

	data.playerID = m_ID;
	data.scale = m_Transform.GetScale();

	std::vector<uint8_t> buf = MakePacket<ScaleData>(PacketType::SCALE, data);
	m_Client->SendData(buf.data(), (unsigned int)buf.size());
}

void NetworkPlayer::SendTransformData()
{
	TransformData data;

	data.playerID = m_ID;
	data.pos = m_Transform.GetPosition();
	data.rot = m_Transform.GetRotation();
	data.scale = m_Transform.GetScale();

	std::vector<uint8_t> buf = MakePacket<TransformData>(PacketType::TRANSFORM, data);
	m_Client->SendData(buf.data(), (unsigned int)buf.size());
}
