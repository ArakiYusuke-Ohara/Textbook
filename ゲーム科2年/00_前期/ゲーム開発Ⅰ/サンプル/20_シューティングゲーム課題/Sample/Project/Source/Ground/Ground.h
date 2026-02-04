#pragma once

#include "DxLib.h"

class Ground
{
public:
	Ground();
	~Ground();

public:
	void Init();
	void Load(const char* path);
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

public:
	void SetScrollSpeed(float speed) { m_ScrollSpeed = speed; }

private:
	int m_Handle;
	float m_TextureV;
	float m_ScrollSpeed;
};
