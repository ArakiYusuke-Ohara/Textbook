#include <iostream>
#include "Food/Fruit.h"

using namespace std;

int main()
{
	Fruit* fruit = new Fruit;

	// FruitはFoodを継承しているので値段を設定できる
	fruit->SetPrice(100);

	// Fruitなので農場名を設定できる
	fruit->SetFarmName("荒木農園");

	// 画面表示
	cout << "生産地：" << fruit->GetFarmName() << endl;
	cout << "値段　：" << fruit->GetPrice() << "円" << endl;

	return 0;
}

