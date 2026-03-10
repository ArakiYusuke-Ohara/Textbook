#include "Enemy.h"
#include <iostream>

using namespace std;

// 小技：初期化リストによるメンバ変数の初期化 こっちの方が処理効率が良い
Enemy::Enemy()
	: m_Handle(-1)
	, m_PosX(0.0f)
	, m_PosY(0.0f)
	, m_MoveX(0.0f)
	, m_MoveY(0.0f)
{
	cout << "Enemyのコンストラクタ" << endl;
}

Enemy::~Enemy()
{
	cout << "Enemyのデストラクタ" << endl;
}

void Enemy::Init()
{
	cout << "Enemy初期化" << endl;
}

void Enemy::Step()
{
	cout << "Enemyステップ" << endl;
}

void Enemy::Draw()
{
	cout << "Enemy描画" << endl;
}

