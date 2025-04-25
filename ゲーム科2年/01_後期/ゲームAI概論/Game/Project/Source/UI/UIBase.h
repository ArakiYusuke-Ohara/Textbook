#pragma once

#include "DxLib.h"

class UIBase
{
public:
	UIBase();
	virtual ~UIBase();

public:
	virtual void Init();
	virtual void Load();
	virtual void Start();
	virtual void Step();
	virtual void Update();
	virtual void Draw();
	virtual void Fin();

public:
	VECTOR GetPos() const { return m_Pos; }

	void SetPos(VECTOR pos) { m_Pos = pos; }

protected:
	VECTOR m_Pos;
};
