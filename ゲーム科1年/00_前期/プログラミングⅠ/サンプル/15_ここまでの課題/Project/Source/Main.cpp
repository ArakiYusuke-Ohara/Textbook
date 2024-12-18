#include <stdio.h>

int main(void)
{
	long long int total = 0;
	long long int num = 0;

	for (int count = 1; count <= 3; count++)
	{
		printf_s("数値を入力してください(%d回目)\n", count);
		scanf_s("%lld", &num);

		total += num;
	}

	printf_s("数値の合計は%lldです\n", total);

		getchar();
		getchar();

	return 0;
}

//int main(void)
//{
//	float total = 0.0f;
//	float num = 0.0f;
//
//	while (1)
//	{
//		printf_s("数値を入力");
//		scanf_s("%f", &num);
//
//		if (num <= 0.0f)
//		{
//			break;
//		}
//		else if (num <= 5.0f)
//		{
//			total *= num;
//		}
//		else if (num <= 10.0f)
//		{
//			total += num;
//		}
//		else
//		{
//			break;
//		}
//	}
//
//	printf_s("total = %f", total);
//
//	getchar();
//	getchar();
//
//	return 0;
//}
