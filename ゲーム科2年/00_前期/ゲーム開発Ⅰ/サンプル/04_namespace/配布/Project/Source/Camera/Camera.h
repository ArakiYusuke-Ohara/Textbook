#pragma once
#include "DxLib.h"

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
	VECTOR m_Target;
	VECTOR m_UpVec;
};