#include "NetworkPlayer.h"
#include "../Network/Client.h"

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
		case Client::State::OFFLINE: UpdateOffline(); break;
		case Client::State::ONLINE: UpdateOnline(); break;
	}
}

void NetworkPlayer::UpdateOffline()
{
	// とくにやることなし
}

void NetworkPlayer::UpdateOnline()
{
	// 移動とか
	Player::Step();

	// 移動したらサーバーに座標を送信

	// 拡縮したらサーバーにスケールを送信

	// 回転したらサーバーに回転値を送信
}

