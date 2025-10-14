#pragma once
#include "../Memory/Memory.h"

class Transform;
class Splite;
class Controller2D;

class Player
{
public:
	Player();
	~Player();

	void Init();
	void Load();
	void Update();
	void Draw();

	void SetMoveSpeed(float speed) { m_MoveSpeed = speed; }
	void SetScaleSpeed(float speed) { m_ScaleSpeed = speed; }
	void SetRotSpeed(float speed) { m_RotSpeed = speed; }

private:
	float m_MoveSpeed;
	float m_ScaleSpeed;
	float m_RotSpeed;
	UniquePtr<Transform> m_Transform;
	UniquePtr<Splite> m_Splite;
	UniquePtr<Controller2D> m_Controller;
};
