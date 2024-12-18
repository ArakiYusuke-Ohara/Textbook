#include <iostream>
#include "Food/Fruit.h"

using namespace std;

//int main()
//{
//	// 食べ物と果物を生成
//	Food food;
//	Fruit fruit;
//
//	// 果物を設定
//	fruit.SetPrice(100);
//	fruit.SetFarmName("藪田果樹園");
//
//	// 派生クラスは基底クラスに代入できる
//	// あまり好ましい処理でないので警告は出る
//	food = fruit;
//
//	// 画面表示
//	cout << "値段：" << food.GetPrice() << "円" << endl;
//
//	return 0;
//}

//int main()
//{
//	// 食べ物と果物を生成
//	Food food;
//	Fruit fruit;
//
//	// 食べ物を設定
//	food.SetPrice(100);
//
//	// 基底クラスから派生クラスへの代入はできない
//	fruit = food;
//
//	// 画面表示
//	cout << "値段：" << fruit.GetPrice() << "円" << endl;
//
//	return 0;
//}

int main()
{
	// 食べ物と果物を生成
	Food* food;
	Fruit* fruit = new Fruit;

	// ポインタでも代入可能
	food = fruit;

	// 食べ物を設定
	food->SetPrice(100);


	// 画面表示
	cout << "値段：" << fruit->GetPrice() << "円" << endl;

	return 0;
}

