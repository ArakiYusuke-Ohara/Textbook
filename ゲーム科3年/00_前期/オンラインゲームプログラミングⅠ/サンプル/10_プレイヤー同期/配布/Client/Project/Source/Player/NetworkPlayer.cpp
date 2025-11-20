#include "NetworkPlayer.h"
#include "../Network/Client.h"
#include "../MyMath/MyMath.h"
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

	// 移動したらサーバーに座標を送信
}

