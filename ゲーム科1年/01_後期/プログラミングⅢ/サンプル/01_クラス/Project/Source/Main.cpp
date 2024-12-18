#include <iostream>
#include "Orange/Orange.h"

int main()
{
	// クラスを生成する
	OrangeBox orangeBoxA;
	OrangeBox orangeBoxB;

	// 箱の中を空にする
	orangeBoxA.Empty();
	orangeBoxB.Empty();

	// 箱にオレンジを追加する
	orangeBoxA.Add(10);
	orangeBoxB.Add(100);

	// 箱のオレンジを削除する
	orangeBoxA.Delete(5);
	orangeBoxB.Delete(50);

	// 箱の中のオレンジの数を取得する
	int orangeNumA = orangeBoxA.GetTotal();
	int orangeNumB = orangeBoxB.GetTotal();

	// オレンジの数をコンソールに出力する
	std::cout << "オレンジ箱Aには" << orangeNumA << "個ある" << std::endl;
	std::cout << "オレンジ箱Bには" << orangeNumB << "個ある" << std::endl;

	return 0;
}


