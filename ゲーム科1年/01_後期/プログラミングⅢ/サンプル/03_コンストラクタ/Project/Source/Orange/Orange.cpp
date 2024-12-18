#include "Orange.h"

OrangeBox::OrangeBox()
{
	m_Total = 0;
}

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

