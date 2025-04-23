#pragma once

#include "DxLib.h"
#include "ItemParameter.h"

class Item
{
public:
	Item();
	~Item();

public:
	void Init();
	void Load();
	void Step();
	void Update();
	void Draw();
	void Fin();
	Item* Clone();

public:
	bool IsActive() const { return m_Active; }

	void SetActive(bool active) { m_Active = active; }
	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetParam(const ItemParameter* param) { m_Param = param; }

private:
	bool m_Active;
	int m_Handle;
	VECTOR m_Pos;
	const ItemParameter* m_Param;
};