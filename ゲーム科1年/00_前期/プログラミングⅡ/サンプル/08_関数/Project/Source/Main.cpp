#include <stdio.h>

// 関数のプロトタイプ宣言
int Add(int numA, int numB);	// 足し算する関数

int main(void)
{
	int japanese = 80;	// 国語の得点
	int math = 70;		// 数学の得点

	// 関数を呼び出す
	// returnされたものがtotalに入る
	int total = Add(japanese, math);

	// 画面表示
	printf_s("国語 ＋ 数学 ＝ %d\n", total);

	return 0;
}

// 足し算する関数の定義
// こういう書き方もできる
int Add(int numA, int numB)
{
	return numA + numB;
}
