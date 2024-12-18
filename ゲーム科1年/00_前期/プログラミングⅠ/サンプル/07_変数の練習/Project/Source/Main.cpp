#include <stdio.h>

int main(void)
{
	short int numA = 10;
	short int numB = -200;
	unsigned int numC = 1000000000;
	unsigned long long int numD = 10000000000000000000;
	float numE = -4.5f;

	printf_s("‡@\n%d\n%d\n%d\n", numA, numB, numC);
	printf_s("‡A\n%llu\n%f\n", numD, numE);

	return 0;
}
