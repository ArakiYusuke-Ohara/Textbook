#include <stdio.h>

//int main(void)
//{
//	int numA = 0;
//
//	printf_s("numAの値を入力してください\n");
//	scanf_s("%d", &numA);
//
//	if (numA == 10)
//	{
//		printf_s("numAは10です");
//	}
//
//	return 0;
//}

//int main(void)
//{
//	int numA = 0;
//
//	printf_s("numAの値を入力してください\n");
//	scanf_s("%d", &numA);
//
//	if (numA != 10)
//	{
//		printf_s("numAは10ではありません");
//	}
//	else
//	{
//		printf_s("numAは10です");
//	}
//
//	return 0;
//}

//int main(void)
//{
//	int numA = 0;
//
//	printf_s("numAの値を入力してください\n");
//	scanf_s("%d", &numA);
//
//	if (numA < 10)
//	{
//		printf_s("numAは10よりも小さいです");
//	}
//	else if (numA > 10)
//	{
//		printf_s("numAは10よりも大きいです");
//	}
//	else
//	{
//		printf_s("numAは10です");
//	}
//
//	return 0;
//}

//int main(void)
//{
//	int numA = 0;
//
//	printf_s("numAの値を入力してください\n");
//	scanf_s("%d", &numA);
//
//	if (numA <= 10)
//	{
//		printf_s("numAは10以下です");
//	}
//	else if (numA >= 10)
//	{
//		printf_s("numAは10以上です");
//	}
//
//	return 0;
//}

//int main(void)
//{
//	int numA = 0;
//
//	printf_s("numAの値を入力してください\n");
//	scanf_s("%d", &numA);
//
//	// &&で2つの条件の論理積で判定できる
//	if (numA >= 4 && numA <= 6)
//	{
//		printf_s("numAは4～6です");
//	}
//
//	return 0;
//}

int main(void)
{
	int numA = 0;

	printf_s("numAの値を入力してください\n");
	scanf_s("%d", &numA);

	// ||で2つの条件の論理和で判定できる
	if (numA < 4 || numA > 6)
	{
		printf_s("numAは4～6ではありません");
	}

	return 0;
}
