#pragma once

class Enemy
{
public:
	Enemy();
	~Enemy();

public:
	void Init();
	void Step();
	void Draw();

private:
	int m_Handle;
	float m_PosX;
	float m_PosY;
	float m_MoveX;
	float m_MoveY;
};

