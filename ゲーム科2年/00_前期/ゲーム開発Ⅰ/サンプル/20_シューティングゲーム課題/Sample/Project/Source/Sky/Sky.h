#pragma once

#include "DxLib.h"

class Sky
{
public:
	Sky();
	~Sky();

public:
	void Init();
	void Load(const char* path);
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

private:
	int m_Handle;
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Scale;
};
