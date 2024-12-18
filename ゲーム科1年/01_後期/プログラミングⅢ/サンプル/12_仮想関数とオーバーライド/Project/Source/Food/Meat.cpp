#include "Meat.h"
#include <string.h>
#include <iostream>

using namespace std;

void Meat::SetShopName(const char* name)
{
	if (strnlen_s(name, SHOP_NAME_MAX) >= SHOP_NAME_MAX)
	{
		cout << "文字数オーバーです" << endl;
		return;
	}

	// 農場名を設定
	strcpy_s(m_ShopName, name);
}

void Meat::CalcPrice()
{
	// 本田精肉店のお肉の値段は5%引き
	if (strcmp(m_ShopName, "本田精肉店") == 0)
	{
		m_Price *= 0.95f;
	}
	// 中村精肉店のお肉の値段は10%引き
	else if (strcmp(m_ShopName, "中村精肉店") == 0)
	{
		m_Price *= 0.90f;
	}

}

