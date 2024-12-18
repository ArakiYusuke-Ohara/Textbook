#pragma once

class Character
{
public:
	Character();
	virtual ~Character();

public:
	void SetPos(int x, int y);
	int GetPosX() { return m_PosX; }
	int GetPosY() { return m_PosY; }
	virtual void Draw() = 0;

protected:
	int m_PosX;
	int m_PosY;
};