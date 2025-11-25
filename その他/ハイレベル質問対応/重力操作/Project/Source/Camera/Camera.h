#pragma once
#include "DxLib.h"

class Player;

class Camera
{
public:
	Camera();
	~Camera() = default;

	void Init();
	void Step();
	void Update();

	void SetFollowPlayer(const Player* target) { m_FollowPlayer = target; }

	VECTOR GetForward();
	
private:
	VECTOR m_Pos;
	VECTOR m_Target;
	VECTOR m_UpVec;
	const Player* m_FollowPlayer;
};
