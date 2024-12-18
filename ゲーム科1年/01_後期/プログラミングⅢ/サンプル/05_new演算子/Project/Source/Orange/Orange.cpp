#include "Orange.h"
#include <iostream>

// ‚±‚ê‚ğ‘‚­‚Æstd::‚ğÈ—ª‚Å‚«‚é
using namespace std;

OrangeBox::OrangeBox()
{
	m_Total = 0;
}

OrangeBox::~OrangeBox()
{
	cout << "OrangeBoxI—¹" << endl;
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

