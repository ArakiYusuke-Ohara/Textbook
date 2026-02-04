#pragma once

#include "DxLib.h"

class Floating;

class BGObject
{
public:
	BGObject();
	~BGObject();

public:
	void Create(int handle);
	void Update();
	void Draw();
	void Fin();

public:
	bool IsActive() const { return m_Active; }
	int GetType() const { return m_Type; }
	VECTOR GetPos() const { return m_Pos; }

	void SetActive(bool active) { m_Active = active; }
	void SetFloatingMover(Floating* mover);
	void SetType(int type) { m_Type = type; }
	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetScale(VECTOR scale) { m_Scale = scale; }
	void SetRot(VECTOR rot) { m_Rot = rot; }


private:
	int m_Type;
	bool m_Active;
	int m_Handle;
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Scale;
	Floating* m_FloatingMover;
};
