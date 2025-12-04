#include "Player.h"
#include "../Component/Collision/AABB.h"

// プレイヤーサイズ
constexpr int PLAYER_WIDTH = 64;
constexpr int PLAYER_HEIGHT = 64;


Player::Player()
{
	m_ID = -1;
}

void Player::Init()
{
	AABB2D* aabb = AddComponent<AABB2D>();
	aabb->SetCenter(VGet(PLAYER_WIDTH / 2.0f, PLAYER_HEIGHT / 2.0f, 0.0f));
	aabb->SetSize(VGet(PLAYER_WIDTH, PLAYER_HEIGHT, 0.0f));
}



