#include "PlayerManager.h"
#include "Player.h"
#include "../Network/Client.h"

PlayerManager::PlayerManager()
{
}

PlayerManager::~PlayerManager() = default;

void PlayerManager::Load()
{
	for (auto& player : m_Players)
	{
		player->Load();
	}
}

void PlayerManager::Start()
{
	for (auto& player : m_Players)
	{
		player->Start();
	}
}

void PlayerManager::Step()
{
	for (auto& player : m_Players)
	{
		player->Step();
	}
}

void PlayerManager::Draw()
{
	for (auto& player : m_Players)
	{
		player->Draw();
	}
}

Player& PlayerManager::CreatePlayer()
{
	// ¶¬‚µ‚Ä‰Šú‰»
	UniquePtr<Player> player = MakeUnique<Player>();
	player->Init();

	// ––”ö‚ÉŠi”[
	m_Players.push_back(std::move(player));

	// À‚ÍQÆ“n‚µ‚Ì•û‚ªˆÀ‘S
	return *(m_Players.back().get());
}

