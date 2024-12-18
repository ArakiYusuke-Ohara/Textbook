#include "Enemy.h"
#include <iostream>

using namespace std;

Enemy::Enemy()
{
	m_PosX = 0;
	m_PosY = 0;
}

Enemy::~Enemy()
{
	cout << "Enemy‚ðíœ‚µ‚Ü‚µ‚½" << endl;
}

void Enemy::SetPos(int x, int y)
{
	m_PosX = x;
	m_PosY = y;
}

void Enemy::DrawPos()
{
	cout << "EnemyÀ•W(" << m_PosX << ", " << m_PosY << ")" << endl;
}
