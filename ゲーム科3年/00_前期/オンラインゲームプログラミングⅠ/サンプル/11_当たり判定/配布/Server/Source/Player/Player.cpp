#include "Player.h"
#include "../Component/Collision/AABB.h"
#include "PlayerManager.h"
#include "../Network/NetworkCommonParam.h"

using namespace Network;

// プレイヤーサイズ
constexpr int PLAYER_WIDTH = 64;
constexpr int PLAYER_HEIGHT = 64;

Player::Player() : GameObject()
, m_ID(-1)
, m_NWHandle(-1)
, m_IPAddress{}
{
	m_Type = GameObjectType::PLAYER;
}

void Player::Init(int nwHandle)
{
	// 一旦プレイヤー数をそのままIDにする
	m_ID = PlayerManager::GetInstance()->GetPlayerCount();

	// ハンドルを設定
	m_NWHandle = nwHandle;

	// IPアドレス設定
	GetNetWorkIP(m_NWHandle, &m_IPAddress);

	// 当たり判定を設定
	AABB2D* aabb = AddComponent<AABB2D>();
	aabb->SetCenter(VGet(0.0f, 0.0f, 0.0f));
	aabb->SetSize(VGet(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f));

	// 初期トランスフォーム
	SetPosition(VGet(100.0f, 100.0f, 0.0f));
	SetScale(VGet(1.0f, 1.0f, 1.0f));
}

void Player::Draw()
{
#ifdef _DEBUG
	VECTOR pos = GetPosition();
	DrawFormatString(0, (m_ID - 1) * 20, GetColor(255, 255, 255), "ID:%d POS:[%.2f, %.2f, %.2f]", m_ID, pos.x, pos.y, pos.z);
#endif
}

/// <summary>
/// 死亡したことをプレイヤーに送信する
/// </summary>
void Player::SendDie()
{
	// 通信データサイズ
	size_t dataSize = sizeof(PacketHeader) + sizeof(DieData);

	// パケット ＋ データを格納するバッファー
	std::vector<uint8_t> buffer(dataSize);

	PacketHeader header = {};
	header.type = PacketType::DIE;
	header.size = sizeof(DieData);

	// ID設定
	DieData data = {};
	data.playerID = m_ID;

	// パケットをバッファーに入れる
	memcpy_s(buffer.data(), buffer.size(), &header, sizeof(PacketHeader));
	// パケットの後ろにデータを入れる
	memcpy_s(buffer.data() + sizeof(PacketHeader), buffer.size() - sizeof(PacketHeader), &data, sizeof(DieData));

	// 全クライアントに送信
	auto players = PlayerManager::GetInstance()->GetPlayers();
	for (const auto& player : players)
	{
		NetWorkSend(player->GetNetworkHandle(), reinterpret_cast<char*>(buffer.data()), (int)buffer.size());
	}
}

void Player::OverlapGameObject(GameObject& other)
{
	// プレイヤーに当たった
	if (other.GetType() == GameObjectType::PLAYER)
	{
		// 非アクティブ
		m_IsActive = false;

		// 死亡を送信

	}
}
