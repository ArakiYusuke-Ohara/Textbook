#include <stdio.h>

int main(void)
{
	// numberAという箱に10を入れて記憶
	int numberA = 0;

	// numberBという箱に20を入れて記憶
	int numberB = 0;

	// 覚えておいたnumberAを画面に表示
	printf_s("numberA = %d", numberA);

	// 改行する
	printf_s("\n");

	// 覚えておいたnumberBを画面に表示
	printf_s("numberB = %d", numberB);

	return 0;
}
