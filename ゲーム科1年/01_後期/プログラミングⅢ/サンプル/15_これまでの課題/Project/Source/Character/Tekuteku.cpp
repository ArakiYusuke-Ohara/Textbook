#include "Tekuteku.h"
#include <iostream>

using namespace std;

Tekuteku::Tekuteku()
{
	m_WalkSpeed = 0;

	cout << "Tekuteku¶¬" << endl;
}

Tekuteku::~Tekuteku()
{
	cout << "Tekutekuíœ" << endl;
}

void Tekuteku::Walk()
{
	m_PosX -= m_WalkSpeed;
}

void Tekuteku::Draw()
{
	cout << "TekutekuÀ•W(" << m_PosX << ", " << m_PosY << ")" << endl;
}
