#pragma once
#include "Player.h"

class Client;

class NetworkPlayer : public Player
{
public:
	NetworkPlayer(const Client* client, int id, bool isSelf);
	virtual ~NetworkPlayer();

	void Step() override;

	int GetID() const { return m_ID; }

	void SetServerPosition(const VECTOR& pos) { m_ServerTransform.SetPosition(pos); }
	void SetServerRotation(const VECTOR& rot) { m_ServerTransform.SetRotation(rot); }
	void SetServerScale(const VECTOR& scale) { m_ServerTransform.SetScale(scale); }

	void StepOffline();
	void StepOnline();

private:
	void SendPosData();
	void SendRotData();
	void SendScaleData();
	void SendTransformData();

private:
	bool m_IsSelf;					// 自分自身が操作するかどうか
	int m_ID;						// 識別ID
	const Client* m_Client;			// 通信用クライアントクラス
};
