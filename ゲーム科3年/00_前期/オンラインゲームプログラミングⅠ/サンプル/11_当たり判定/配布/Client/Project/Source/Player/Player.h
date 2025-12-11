#pragma once
#include "DxLib.h"
#include "../Memory/Memory.h"
#include "../Object/GameObject.h"

class Splite;
class Controller2D;

class Player : public GameObject
{
public:
	Player();
	virtual ~Player();

	void Init();
	void Load();
	void Start();
	virtual void Step();
	virtual void Draw();

	// アクセサ
	void SetPos(const VECTOR& pos) { m_Transform.SetPosition(pos); }
	void SetRot(const VECTOR& rot) { m_Transform.SetRotation(rot); }
	void SetScale(const VECTOR& scale) { m_Transform.SetScale(scale); }

	void Die();

protected:
	bool m_IsActive;
	float m_MoveSpeed;
	float m_ScaleSpeed;
	float m_RotSpeed;
	Splite* m_Splite;
	Controller2D* m_Controller;
};
