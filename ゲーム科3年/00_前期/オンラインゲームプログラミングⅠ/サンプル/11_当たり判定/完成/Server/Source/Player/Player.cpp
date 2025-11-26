#include "Player.h"
#include "../Component/Collision/AABB.h"
#include "../Network/NetworkCommonParam.h"

Player::Player()
{
	m_ID = -1;
}

void Player::Init()
{
	// AABB‚ð’Ç‰Á
	SharedPtr<AABB> aabb = MakeShared<AABB>();
	aabb->SetSize(VGet(Network::PLAYER_WIDTH, Network::PLAYER_HEIGHT, 0));

	AddComponent(aabb);
}



