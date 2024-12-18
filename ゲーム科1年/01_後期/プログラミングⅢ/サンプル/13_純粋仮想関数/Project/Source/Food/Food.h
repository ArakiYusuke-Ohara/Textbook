#pragma once

class Food
{
public:
	void SetPrice(int price) { m_Price = price; }
	int GetPrice() { return m_Price; }
	virtual void CalcPrice() = 0;

protected:
	int m_Price;
};

