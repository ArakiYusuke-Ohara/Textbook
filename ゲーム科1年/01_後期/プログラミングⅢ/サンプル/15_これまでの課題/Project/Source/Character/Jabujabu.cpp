#include "Jabujabu.h"
#include <iostream>

using namespace std;

Jabujabu::Jabujabu()
{
	m_SwimSpeed = 0;

	cout << "Jabujabu¶¬" << endl;
}

Jabujabu::~Jabujabu()
{
	cout << "Jabujabuíœ" << endl;
}

void Jabujabu::Swim()
{
	m_PosX -= m_SwimSpeed;
}

void Jabujabu::Draw()
{
	cout << "JabujabuÀ•W(" << m_PosX << ", " << m_PosY << ")" << endl;
}
