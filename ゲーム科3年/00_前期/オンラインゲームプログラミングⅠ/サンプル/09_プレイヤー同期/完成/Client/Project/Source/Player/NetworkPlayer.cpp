#include "NetworkPlayer.h"
#include "../Network/Client.h"
#include "../MyMath/MyMath.h"
#include "../Network/NetworkUtility.h"
#include "../Component/Splite.h"

// これだけ動いたらサーバーに送信する
constexpr float POS_THRESHOLD = 1.0f;
constexpr float SCALE_THRESHOLD = 0.005f;
constexpr float ROT_THRESHOLD = 0.005f;

NetworkPlayer::NetworkPlayer(const Client* client, int id, bool isSelf) : Player()
, m_IsSelf(isSelf)
, m_ID(id)
, m_Client(client)
{
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

/// <summary>
/// サーバーから受信した座標で描画する
/// </summary>
void NetworkPlayer::Draw()
{
	if (m_Splite)
	{
		m_Splite->SetTransform(m_ServerTransform);
		m_Splite->Draw();
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
	float dist = MyMath::GetDistance(m_Transform.GetPos(), m_ServerTransform.GetPos());
	if (dist >= POS_THRESHOLD)
	{
		isMove = true;
	}

	// 回転したらサーバーに回転値を送信
	dist = MyMath::GetDistance(m_Transform.GetRot(), m_ServerTransform.GetRot());
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
	VECTOR pos = m_Transform.GetPos();
	Network::PosData data;
	data.playerID = m_ID;
	data.pos = pos;

	std::vector<uint8_t> buf = Network::NetworkUtility::MakePosData(data);

	NetWorkSend(m_Client->GetServerHandle(), reinterpret_cast<const char*>(buf.data()), (int)buf.size());
}

void NetworkPlayer::SendRotData()
{
	VECTOR rot = m_Transform.GetRot();
	Network::RotData data;
	data.playerID = m_ID;
	data.rot = rot;

	std::vector<uint8_t> buf = Network::NetworkUtility::MakeRotData(data);

	NetWorkSend(m_Client->GetServerHandle(), reinterpret_cast<const char*>(buf.data()), (int)buf.size());
}

void NetworkPlayer::SendScaleData()
{
	Network::ScaleData data;

	data.playerID = m_ID;
	data.scale = m_Transform.GetScale();

	std::vector<uint8_t> buf = Network::NetworkUtility::MakeScaleData(data);

	NetWorkSend(m_Client->GetServerHandle(), reinterpret_cast<const char*>(buf.data()), (int)buf.size());
}

void NetworkPlayer::SendTransformData()
{
	Network::TransformData data;

	data.playerID = m_ID;
	data.pos = m_Transform.GetPos();
	data.rot = m_Transform.GetRot();
	data.scale = m_Transform.GetScale();

	std::vector<uint8_t> buf = Network::NetworkUtility::MakeTransformData(data);

	NetWorkSend(m_Client->GetServerHandle(), reinterpret_cast<const char*>(buf.data()), (int)buf.size());
}
