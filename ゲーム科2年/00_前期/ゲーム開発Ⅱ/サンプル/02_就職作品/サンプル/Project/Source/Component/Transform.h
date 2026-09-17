#pragma once
#include "DxLib.h"
#include "Component.h"

class Transform : public Component
{
public:
	Transform() = default;
	virtual ~Transform() = default;

	VECTOR GetPos() const { return m_Pos; }
	VECTOR GetRotate() const { return m_Rotate; }
	VECTOR GetScale() const { return m_Scale; }

	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetRotate(VECTOR rotate) { m_Rotate = rotate; }
	void SetScale(VECTOR scale) { m_Scale = scale; }

private:
	VECTOR m_Pos;
	VECTOR m_Rotate;
	VECTOR m_Scale;
};