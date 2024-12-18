#include <stdio.h>

int main(void)
{
	int numA = 0;
	int numB = 0;

	printf_s("numAの値を入力してください\n");
	scanf_s("%d", &numA);

	printf_s("numBの値を入力してください\n");
	scanf_s("%d", &numB);

	printf_s("numA + numB = %d\n", numA + numB);
	printf_s("numA - numB = %d\n", numA - numB);
	printf_s("numA * numB = %d\n", numA * numB);
	printf_s("numA / numB = %d\n", numA / numB);

	return 0;
}

int main(void)
{
	float numA = 0;
	float numB = 0;

	printf_s("numAの値を入力してください\n");
	scanf_s("%f", &numA);

	printf_s("numBの値を入力してください\n");
	scanf_s("%f", &numB);

	printf_s("numA + numB = %f\n", numA + numB);
	printf_s("numA - numB = %f\n", numA - numB);
	printf_s("numA * numB = %f\n", numA * numB);
	printf_s("numA / numB = %f\n", numA / numB);

	return 0;
}
