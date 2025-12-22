#pragma once
#include "Player.h"

class Client;

class NetworkPlayer : public Player
{
public:
	NetworkPlayer(int id, bool isSelf);
	NetworkPlayer(const Client* client, int id, bool isSelf);
	virtual ~NetworkPlayer();

	void Step() override;

	int GetID() const { return m_ID; }

	void SetServerPosition(const VECTOR& pos) { m_ServerTransform.SetPosition(pos); }
	void SetServerRotation(const VECTOR& rot) { m_ServerTransform.SetRotation(rot); }
	void SetServerScale(const VECTOR& scale) { m_ServerTransform.SetScale(scale); }

private:
	bool m_IsSelf;					// ©•ª©g‚ª‘€ì‚·‚é‚©‚Ç‚¤‚©
	int m_ID;						// ¯•ÊID
};
