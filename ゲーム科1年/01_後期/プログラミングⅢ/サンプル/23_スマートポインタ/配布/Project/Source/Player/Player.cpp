#include "Player.h"
#include <iostream>

using namespace std;

// 小技：初期化リストによるメンバ変数の初期化 こっちの方が処理効率が良い
Player::Player()
	: m_Handle(-1)
	, m_PosX(0.0f)
	, m_PosY(0.0f)
	, m_MoveX(0.0f)
	, m_MoveY(0.0f)
{
	cout << "Playerのコンストラクタ" << endl;
}

Player::~Player()
{
	cout << "Playerのデストラクタ" << endl;
}

void Player::Move()
{
	cout << "Playerの移動" << endl;
}

void Player::Jump()
{
	cout << "Playerのジャンプ" << endl;
}

void Player::Attack()
{
	cout << "Playerの攻撃" << endl;
}
