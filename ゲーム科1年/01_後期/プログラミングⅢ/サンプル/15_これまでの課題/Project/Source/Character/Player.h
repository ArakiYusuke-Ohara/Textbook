#pragma once

#include "Character.h"

class Player : public Character
{
public:
	Player();
	~Player();

public:
	void SetDirection(int direction) { m_Direction = direction; }
	void MoveForward();			// 前進
	void Jump();				// ジャンプ
	void Draw() override;	// 座標表示

private:
	int m_Direction;	// 向いている方向(0:上 1:右 2:下 3:左)
	bool m_JumpFlag;	// ジャンプしたかどうか
};
