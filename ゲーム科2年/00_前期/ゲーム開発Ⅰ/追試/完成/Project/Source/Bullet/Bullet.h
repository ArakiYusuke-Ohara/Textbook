#pragma once
#include "DxLib.h"

class CollisionSphere;

class Bullet
{
public:
	Bullet();
	~Bullet();

	void Init();
	void Step();
	void Draw();

	void Fire(VECTOR pos, VECTOR rot, float speed);
	void Hit();

	bool IsActive() const { return m_Active; }
	CollisionSphere* GetCollision() const { return m_Collision; }

	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetRot(VECTOR rot) { m_Rot = rot; }
	void SetSpeed(float speed) { m_Speed = speed; }

private:
	bool m_Active;
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Move;
	int m_Life;
	float m_Rad;
	float m_Speed;
	CollisionSphere* m_Collision;
};