#pragma once
#include "DxLib.h"

// ÉJÉÅÉâÉNÉâÉX
class DebugCamera
{
public:
	DebugCamera();
	~DebugCamera();

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

public:
	void SetRot(VECTOR rot) { m_Rot = rot; }
	void SetTarget(VECTOR target) { m_Target = target; }

private:
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Target;
	VECTOR m_UpVec;
	float m_Move;
};