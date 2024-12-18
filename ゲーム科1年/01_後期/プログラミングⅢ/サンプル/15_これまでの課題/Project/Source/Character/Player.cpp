#include "Player.h"
#include <iostream>

using namespace std;

Player::Player()
{
	m_Direction = 0;
	m_JumpFlag = false;

	cout << "Player生成" << endl;
}

Player::~Player()
{
	cout << "Player削除" << endl;
}

void Player::MoveForward()
{
	// 向いている方向に合わせて移動
	switch (m_Direction)
	{
		case 0:
			m_PosY -= 10;
			break;

		case 1:
			m_PosX += 10;
			break;

		case 2:
			m_PosY += 10;
			break;

		case 3:
			m_PosX -= 10;
			break;
	}
}

void Player::Jump()
{
	m_JumpFlag = true;
}

void Player::Draw()
{
	// 座標表示
	cout << "Player座標(" << m_PosX << ", " << m_PosY << ")" << endl;

	// ジャンプしたならジャンプと表示
	if (m_JumpFlag)
	{
		cout << "Playerジャンプ！！" << endl;
		// 表示したらフラグを折っておく
		m_JumpFlag = false;
	}
}

