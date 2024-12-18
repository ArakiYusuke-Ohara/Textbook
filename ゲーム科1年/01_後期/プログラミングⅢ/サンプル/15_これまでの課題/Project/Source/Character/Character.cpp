#include "Character.h"
#include <iostream>

using namespace std;

Character::Character()
{
	m_PosX = 0;
	m_PosY = 0;

	cout << "Character¶¬" << endl;
}

Character::~Character()
{
	cout << "Characteríœ" << endl;
}

void Character::SetPos(int x, int y)
{
	m_PosX = x;
	m_PosY = y;
}
