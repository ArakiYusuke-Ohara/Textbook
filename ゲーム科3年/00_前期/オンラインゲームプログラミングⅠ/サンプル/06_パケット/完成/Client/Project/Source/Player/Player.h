#pragma once
#include "DxLib.h"
#include "../Memory/Memory.h"
#include "../Component/Transform.h"

class Splite;
class Controller2D;

class Player
{
public:
	Player();
	~Player();

	virtual void Init();
	void Load();
	void Start();
	virtual void Step();
	void Draw();

protected:
	float m_MoveSpeed;
	float m_ScaleSpeed;
	float m_RotSpeed;
	Transform m_Transform;
	UniquePtr<Splite> m_Splite;
	UniquePtr<Controller2D> m_Controller;
};
