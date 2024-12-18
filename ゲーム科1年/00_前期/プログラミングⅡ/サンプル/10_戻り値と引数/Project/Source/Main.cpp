#include <stdio.h>

// 関数のプロトタイプ宣言
int Add(int numA, int numB);		// 戻り値あり　引数あり
void PrintJapaneseAndMath();		// 戻り値なし　引数なし
int  AddJapaneseAndMath();			// 戻り値あり　引数なし
void PrentAdd(int numA, int numB);	// 戻り値なし　引数あり

int main(void)
{
	PrintJapaneseAndMath();
	return 0;
}

// 足し算する関数の定義
// こういう書き方もできる
int Add(int numA, int numB)
{
	return numA + numB;
}

void PrintJapaneseAndMath()
{
	int japanese = 80;	// 国語の得点
	int math = 70;		// 数学の得点

	// 関数を呼び出す
	// returnされたものがtotalに入る
	int total = Add(japanese, math);

	// 画面表示
	printf_s("国語 ＋ 数学 ＝ %d\n", total);

}

int  AddJapaneseAndMath()
{
	int japanese = 80;	// 国語の得点
	int math = 70;		// 数学の得点

	return japanese + math;
}

void PrentAdd(int numA, int numB)
{
	printf_s("国語 ＋ 数学 ＝ %d\n", numA + numB);
}

