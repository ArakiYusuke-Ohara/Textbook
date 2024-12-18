#include "Fruit.h"
#include <string.h>
#include <iostream>

using namespace std;

void Fruit::SetFarmName(const char* name)
{
	if (strnlen_s(name, FARM_NAME_MAX) >= FARM_NAME_MAX)
	{
		cout << "文字数オーバーです" << endl;
		return;
	}

	// 農場名を設定
	strcpy_s(m_FarmName, name);
}

