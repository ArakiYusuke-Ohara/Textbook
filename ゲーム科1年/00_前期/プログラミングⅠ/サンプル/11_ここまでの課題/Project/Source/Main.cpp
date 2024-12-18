#include <stdio.h>

int main(void)
{
	float numA = 0;
	float numB = 0;
	char calc = ' ';

	printf_s("numA‚Ì’l‚ð“ü—Í\n");
	scanf_s("%f", &numA);

	printf_s("‰‰ŽZŽq‚ð“ü—Í\n");
	scanf_s(" %c", &calc);

	printf_s("numB‚Ì’l‚ð“ü—Í\n");
	scanf_s("%f", &numB);

	if (calc == '+')
	{
		printf_s("numA + numB = %f", numA + numB);
	}
	else if (calc == '-')
	{
		printf_s("numA - numB = %f", numA - numB);
	}
	else if (calc == '*')
	{
		printf_s("numA * numB = %f", numA * numB);
	}
	else if (calc == '/')
	{
		printf_s("numA + numB = %f", numA / numB);
	}

	// “ü—Í‘Ò‚¿‚·‚é‚½‚ß‚Ìgetchar
	getchar();
	getchar();

	return 0;
}
