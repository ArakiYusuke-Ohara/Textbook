#include "Orange.h"

void OrangeBox::Add(int num)
{
	m_Total += num;
}

void OrangeBox::Delete(int num)
{
	m_Total -= num;
}

void OrangeBox::Empty()
{
	m_Total = 0;
}

