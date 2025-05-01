#pragma once

#include "DxLib.h"

class UIBase
{
public:
	UIBase();
	virtual ~UIBase();

public:
	virtual void Init();
	virtual void Step();
	virtual void Update();
	virtual void Draw();
	virtual void Fin();
	virtual UIBase* Clone() = 0;

public:
	VECTOR GetPos() const { return m_Pos; }
	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }

	void SetPos(VECTOR pos) { m_Pos = pos; }

protected:
	VECTOR m_Pos;
	int m_Width;
	int m_Height;
};
