#pragma once

class Food
{
public:
	void SetPrice(int price) { m_Price = price; }
	int GetPrice() { return m_Price; }

protected:
	int m_Price;
};

