#include <stdio.h>

//int main(void)
//{
//	// int型を10個まとめて配列で宣言する
//	// { 0 }でまとめて0初期化できる
//	int buffer[10] = { 0 };
//
//	// 配列の要素は添字（インデックス）を使うと取り出せる
//	// ただし添字は0から数える
//	buffer[0] = 100;
//	buffer[2] = 35;
//
//	// for文を使えば配列の中を網羅することができる
//	for (int i = 0; i < 10; i++)
//	{
//		printf_s("buffer[%d] = %d\n", i, buffer[i]);
//	}
//
//	return 0;
//}

//int main(void)
//{
//	// カンマ区切りで各要素の初期値を設定できる
//	int buffer[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//
//	// for文を使えば配列の中を網羅することができる
//	for (int i = 0; i < 10; i++)
//	{
//		printf_s("buffer[%d] = %d\n", i, buffer[i]);
//	}
//
//	return 0;
//}

//int main(void)
//{
//	// char型の配列は文字列として使える
//	char lastName[64];	// 半角64文字、全角は32文字まで
//	char firstName[64];	// 半角64文字、全角は32文字まで
//
//	printf_s("苗字を入力\n");
//	scanf_s("%s", lastName);	// 配列にscanfする場合は&マークは不要
//
//	printf_s("名前を入力\n");
//	scanf_s("%s", firstName);	// 配列にscanfする場合は&マークは不要
//
//	// printfするときも配列名だけ
//	printf_s("名前：%s %s", lastName, firstName);
//
//	return 0;
//}

int main(void)
{
	// 文字列は直接初期化できる
	char name[64] = "荒木 優介";

	// printfするときも配列名だけ
	printf_s("名前：%s", name);

	return 0;
}
