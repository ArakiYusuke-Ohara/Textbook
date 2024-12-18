#pragma once
#include "DxLib.h"

class Player;

// ƒJƒƒ‰ƒNƒ‰ƒX
class Camera
{
public:
	Camera();
	~Camera();

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

private:
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Target;
	VECTOR m_UpVec;
	Player* m_TargetPlayer;
};