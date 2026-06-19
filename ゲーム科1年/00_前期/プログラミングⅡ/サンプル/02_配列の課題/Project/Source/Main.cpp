#include <stdio.h>

int main(void)
{
	// int型20個の配列
	int buffer[20] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
	// ポインターに配列を参照させる
	int* pointer = buffer;
	// 合計を保存する変数
	int total = 0;

	// 20回回るfor文
	for (int i = 0; i < 20; i++, pointer++)
	{
		// 問題：添え字[i]を使わずポインターを使って加算しよう
		total += *pointer;
	}

	// 出力
	printf_s("配列の中の数値の合計は%dです", total);

	return 0;
}

//int main(void)
//{
//	// 3行2列の行列
//	float matrix[3][2] = {
//		{1.0f, 2.0f},
//		{3.0f, 4.0f},
//		{5.0f, 6.0f},
//	};
//
//	// 合計を保存する変数
//	float total = 0.0f;
//
//	// 2重for文で2次元配列を網羅する
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < 2; j++)
//		{
//			// 足し算
//			total += matrix[i][j];
//		}
//	}
//
//	printf_s("配列の中の数値の合計は%fです", total);
//
//	return 0;
//}

//int main(void)
//{
//	char message[5][128] =
//	{
//		"昨日のニンテンドーダイレクトで",
//		"とても印象に残ったのは",
//		"朧村正のリメイクと",
//		"アトリエの新作でした",
//		"キンハーⅣは大丈夫なのか。。。",
//	};
//
//	for (int i = 0; i < 5; i++)
//	{
//		getchar();
//		printf_s("%s", message[i]);
//	}
//	printf_s("\n");
//
//	return 0;
//}
