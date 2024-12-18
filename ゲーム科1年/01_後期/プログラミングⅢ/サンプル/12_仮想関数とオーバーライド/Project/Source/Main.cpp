#include <iostream>
#include "Food/Fruit.h"
#include "Food/Meat.h"

using namespace std;

int main()
{
	// r–Ø”_‰€‚Ì‰Ê•¨‚ð¶¬
	Fruit* arakiFruit = new Fruit;
	arakiFruit->SetPrice(100);
	arakiFruit->SetFarmName("r–Ø”_‰€");

	// –{“c¸“÷“X‚Ì“÷‚ð¶¬
	Meat* hondaMeat = new Meat;
	hondaMeat->SetPrice(500);
	hondaMeat->SetShopName("–{“c¸“÷“X");

	// r–Ø”_‰€‚Ì‰Ê•¨‚ðFoodƒ|ƒCƒ“ƒ^‚ÉŽQÆ‚³‚¹‚Ä
	Food* food = arakiFruit;
	// ’l’i•â³ŠÖ”‚ðŒÄ‚Ô
	food->CalcPrice();

	// ‰æ–Ê•\Ž¦
	cout << "r–Ø”_‰€‚Ì‰Ê•¨‚Í" << food->GetPrice() << "‰~" << endl;

	// –{“c¸“÷“X‚Ì“÷‚ðFoodƒ|ƒCƒ“ƒ^‚ÉŽQÆ‚³‚¹‚Ä
	food = hondaMeat;
	// ’l’i•â³ŠÖ”‚ðŒÄ‚Ô
	food->CalcPrice();

	// ‰æ–Ê•\Ž¦
	cout << "–{“c¸“÷“X‚Ì‚¨“÷‚Í" << food->GetPrice() << "‰~" << endl;

	// íœ
	delete arakiFruit;
	delete hondaMeat;

	return 0;
}