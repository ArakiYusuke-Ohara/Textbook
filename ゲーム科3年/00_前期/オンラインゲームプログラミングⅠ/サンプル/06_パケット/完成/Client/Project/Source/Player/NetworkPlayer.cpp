#include "NetworkPlayer.h"
#include "../Network/Client.h"
#include "../MyMath/MyMath.h"
#include "../Network/NetworkUtility.h"
#include "../Component/Splite.h"

// これだけ動いたらサーバーに送信する
constexpr float POS_THRESHOLD = 1.0f;
constexpr float SCALE_THRESHOLD = 0.01f;
constexpr float ROT_THRESHOLD = 0.01f;

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

/// <summary>
/// 座標をサーバーに送信
/// </summary>
void NetworkPlayer::SendPosData()
{
	VECTOR pos = m_Transform.GetPos();
	Network::PosData data;
	data.playerID = m_ID;
	data.x = pos.x;
	data.y = pos.y;
	data.z = pos.z;

	std::vector<uint8_t> buf = Network::NetworkUtility::MakePosData(data);

	NetWorkSend(m_Client->GetServerHandle(), reinterpret_cast<const char*>(buf.data()), (int)buf.size());
}
