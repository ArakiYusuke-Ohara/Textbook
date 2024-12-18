#include "Fruit.h"
#include <string.h>
#include <iostream>

using namespace std;

void Fruit::SetFarmName(const char* name)
{
	if (strnlen_s(name, FARM_NAME_MAX) >= FARM_NAME_MAX)
	{
		cout << "•¶Žš”ƒI[ƒo[‚Å‚·" << endl;
		return;
	}

	// ”_ê–¼‚ðÝ’è
	strcpy_s(m_FarmName, name);
}

void Fruit::CalcPrice()
{
	// r–Ø”_‰€‚Ì‰Ê•¨‚Ì’l’i‚Í3%ˆø‚«
	if (strcmp(m_FarmName, "r–Ø”_‰€") == 0)
	{
		m_Price *= 0.97f;
	}
}
