#include "NetworkPlayer.h"
#include "../Network/Client.h"
#include "../MyMath/MyMath.h"

// これだけ動いたらサーバーに送信する
constexpr float POS_THRESHOLD = 0.05f;
constexpr float SCALE_THRESHOLD = 0.01f;
constexpr float ROT_THRESHOLD = 0.01f;


NetworkPlayer::NetworkPlayer() : Player()
{
	m_Client = nullptr;
}

NetworkPlayer::~NetworkPlayer() = default;

void NetworkPlayer::Init()
{
	Player::Init();

	// プレイヤー初期化時に接続
	m_Client = MakeUnique<Client>();
	m_Client->Connect();
}

void NetworkPlayer::Step()
{
	// 通信を更新
	if (m_Client)
	{
		m_Client->Step();
	}

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

void NetworkPlayer::StepOnline()
{
	Transform oldTransform = m_Transform;

	// 移動とか
	Player::Step();

	// 移動したらサーバーに座標を送信
	float dist = MyMath::GetDistance(m_Transform.GetPos(), oldTransform.GetPos());
	if (dist >= POS_THRESHOLD)
	{
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

