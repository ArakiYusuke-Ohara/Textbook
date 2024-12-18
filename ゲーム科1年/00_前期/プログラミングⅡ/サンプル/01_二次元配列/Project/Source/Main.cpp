#include <stdio.h>

//int main(void)
//{
//	// ２次元配列を宣言
//	int matrix[3][5] = { 0 };
//
//	// ２次元なので２つの添字でアクセスする
//	// 添字は[行番号][列番号]となる
//	matrix[0][2] = 50;
//	matrix[1][3] = 20;
//	matrix[2][0] = 100;
//
//	// for文を２重に使えば網羅できる
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < 5; j++)
//		{
//			printf_s("%3d, ", matrix[i][j]);
//		}
//		// 改行
//		printf_s("\n");
//	}
//
//	return 0;
//}

//int main(void)
//{
//	// ２次元配列も{}で分ければ初期値を設定できる
//	int matrix[3][5] =
//	{
//		{1, 2, 3, 4, 5},
//		{6, 7, 8, 9, 10},
//		{11, 12, 13, 14, 15},
//	};
//
//
//	// for文を２重に使えば網羅できる
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < 5; j++)
//		{
//			printf_s("%3d, ", matrix[i][j]);
//		}
//		// 改行
//		printf_s("\n");
//	}
//
//	return 0;
//}

int main(void)
{
	char names[3][32] =
	{
		"荒木",
		"田中",
		"山田"
	};

	for (int i = 0; i < 3; i++)
	{
		printf_s("%s\n", names[i]);
	}

	return 0;
}
