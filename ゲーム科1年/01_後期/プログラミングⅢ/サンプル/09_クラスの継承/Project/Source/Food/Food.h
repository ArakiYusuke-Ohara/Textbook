#pragma once

class Food
{
public:
	void SetPrice(int price) { m_Price = price; }
	int GetPrice() { return m_Price; }

private:
	int m_Price;
};

