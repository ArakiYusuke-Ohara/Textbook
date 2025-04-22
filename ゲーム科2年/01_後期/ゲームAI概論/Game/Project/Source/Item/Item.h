#pragma once

#include "DxLib.h"
#include "ItemParameter.h"

class Item
{
public:
	Item();
	~Item();

public:
	void Load();
	void Step();
	void Update();
	void Draw();
	void Fin();
	Item* Clone();

public:
	void SetParam(const ItemParameter* param) { m_Param = param; }

private:
	int m_Handle;
	VECTOR m_Pos;
	const ItemParameter* m_Param;
};