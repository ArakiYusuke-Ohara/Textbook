#pragma once

class Player
{
public:
	Player();
	~Player();

public:
	void Move();
	void Jump();
	void Attack();

private:
	int m_Handle;
	float m_PosX;
	float m_PosY;
	float m_MoveX;
	float m_MoveY;
};