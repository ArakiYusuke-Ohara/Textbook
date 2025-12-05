#include "Player.h"
#include "../Component/Collision/AABB.h"
#include "PlayerManager.h"

// プレイヤーサイズ
constexpr int PLAYER_WIDTH = 64;
constexpr int PLAYER_HEIGHT = 64;

Player::Player() : GameObject()
, m_ID(-1)
, m_NWHandle(-1)
, m_IPAddress{}
{
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
