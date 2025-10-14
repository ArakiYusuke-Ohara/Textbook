#pragma once
#include "DxLib.h"
#include "../Memory/Memory.h"

class Transform;
class Splite;
class Controller2D;

class Player
{
public:
	Player();
	~Player();

	virtual void Init();
	void Load();
	virtual void Step();
	void Draw();

	void SetPos(VECTOR pos);

private:
	float m_MoveSpeed;
	float m_ScaleSpeed;
	float m_RotSpeed;
	UniquePtr<Transform> m_Transform;
	UniquePtr<Splite> m_Splite;
	UniquePtr<Controller2D> m_Controller;
};
