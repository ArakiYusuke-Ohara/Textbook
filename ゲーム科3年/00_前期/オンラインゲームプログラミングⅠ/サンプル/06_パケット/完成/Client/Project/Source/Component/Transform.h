#pragma once
#include <DxLib.h>

class Transform
{
public:
	Transform();
	~Transform() = default;

public:
	void SetPos(const VECTOR& pos) { m_Pos = pos; }
	void SetRot(const VECTOR& rot) { m_Rot = rot; }
	void SetScale(const VECTOR& scale) { m_Scale = scale; }
	VECTOR GetPos() const { return m_Pos; }
	VECTOR GetRot() const { return m_Rot; }
	VECTOR GetScale() const { return m_Scale; }

private:
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Scale;
};
