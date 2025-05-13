#pragma once
#include "DxLib.h"

// è∞ÉNÉâÉX
class Floor
{
public:
	Floor();
	~Floor();

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

private:
	int m_Handle;
	VECTOR m_Pos;
};
