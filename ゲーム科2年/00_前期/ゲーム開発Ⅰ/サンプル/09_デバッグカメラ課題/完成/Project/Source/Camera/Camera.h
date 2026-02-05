#pragma once
#include "DxLib.h"

// ƒJƒƒ‰ƒNƒ‰ƒX
class Camera
{
public:
	Camera();
	~Camera();

	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

	VECTOR GetPos() const { return m_Pos; }
	VECTOR GetTarget() const { return m_Target; }

private:
	VECTOR m_Pos;
	VECTOR m_Target;
	VECTOR m_UpVec;
};