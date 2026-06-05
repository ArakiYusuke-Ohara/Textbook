#include <stdio.h>

//int main(void)
//{
//	int buffer[20] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
//
//	int total = 0;
//	for (int i = 0; i < 20; i++)
//	{
//		total += buffer[i];
//	}
//
//	printf_s("配列の中の数値の合計は%dです", total);
//
//	return 0;
//}

int main(void)
{
	float matrix[3][2] = {
		{1.0f, 2.0f},
		{3.0f, 4.0f},
		{5.0f, 6.0f},
	};

	float total = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			total += matrix[i][j];
		}
	}

	printf_s("配列の中の数値の合計は%fです", total);

	return 0;
}
