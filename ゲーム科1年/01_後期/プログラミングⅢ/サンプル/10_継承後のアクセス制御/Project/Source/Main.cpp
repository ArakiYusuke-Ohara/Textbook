#include <iostream>
#include "Food/Fruit.h"

using namespace std;

int main()
{
	Fruit* fruit = new Fruit;

	// Fruit‚ÍFood‚ðŒp³‚µ‚Ä‚¢‚é‚Ì‚Å’l’i‚ðÝ’è‚Å‚«‚é
	fruit->SetPrice(100);

	// Fruit‚È‚Ì‚Å”_ê–¼‚ðÝ’è‚Å‚«‚é
	fruit->SetFarmName("r–Ø”_‰€");

	// ’l’i•â³‚ðŒvŽZ
	fruit->CalcPrice();

	// ‰æ–Ê•\Ž¦
	cout << "¶ŽY’nF" << fruit->GetFarmName() << endl;
	cout << "’l’i@F" << fruit->GetPrice() << "‰~" << endl;

	return 0;
}

