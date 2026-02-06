#pragma once
#include "DxLib.h"

// ÉJÉÅÉâÉNÉâÉX
class DebugCamera
{
public:
	DebugCamera();
	~DebugCamera();

	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetTarget(VECTOR target) { m_Target = target; }

private:
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Target;
	VECTOR m_UpVec;
	VECTOR m_Move;
};