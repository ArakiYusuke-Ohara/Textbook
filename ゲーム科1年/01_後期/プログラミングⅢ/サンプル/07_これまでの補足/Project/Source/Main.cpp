#include <iostream>
#include "Orange/Orange.h"

using namespace std;

int main()
{
	// クラスを生成する
	OrangeBox orangeBoxes[3];

	// 全ての箱にオレンジを追加する
	for (int i = 0; i < 3; i++)
	{
		int inputNum = 0;
		cout << i << "番目の箱に入れるオレンジの個数を入力" << endl;
		cin >> inputNum;

		orangeBoxes[i].Empty();
		orangeBoxes[i].Add(inputNum);
	}

	// 全ての箱のオレンジの数を出力
	for (int i = 0; i < 3; i++)
	{
		int orangeNum = orangeBoxes[i].GetTotal();
		cout << "オレンジ箱[" << i << "]には" << orangeNum << "個ある" << endl;
	}

	return 0;
}

int main()
{
	// クラスを生成する
	OrangeBox* orangeBoxes = new OrangeBox[3];

	// 全ての箱にオレンジを追加する
	for (int i = 0; i < 3; i++)
	{
		int inputNum = 0;
		cout << i << "番目の箱に入れるオレンジの個数を入力" << endl;
		cin >> inputNum;

		orangeBoxes[i].Empty();
		orangeBoxes[i].Add(inputNum);
	}

	// 全ての箱のオレンジの数を出力
	for (int i = 0; i < 3; i++)
	{
		int orangeNum = orangeBoxes[i].GetTotal();
		cout << "オレンジ箱[" << i << "]には" << orangeNum << "個ある" << endl;
	}

	delete[] orangeBoxes;

	return 0;
}

