#pragma once

class Enemy
{
public:
	Enemy();
	~Enemy();

public:
	void SetPos(int x, int y);
	void DrawPos();

private:
	int m_PosX;
	int m_PosY;
};