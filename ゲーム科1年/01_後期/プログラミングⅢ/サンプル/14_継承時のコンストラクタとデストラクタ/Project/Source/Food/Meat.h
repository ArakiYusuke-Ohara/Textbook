#pragma once
#include "Food.h"

#define SHOP_NAME_MAX 32

class Meat : public Food
{
public:
	Meat();
	~Meat();

public:
	void SetShopName(const char* name);
	char* GetShopName() { return m_ShopName; }
	void CalcPrice();

private:
	char m_ShopName[SHOP_NAME_MAX];
};

