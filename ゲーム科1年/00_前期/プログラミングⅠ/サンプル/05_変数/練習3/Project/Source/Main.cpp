#include <stdio.h>

int main(void)
{
	// singleCharAという箱に a を入れて記憶
	char singleCharA = 'a';

	// singleCharBという箱に z を入れて記憶
	char singleCharB = 'z';

	// 覚えておいたsingleCharAを画面に表示
	printf_s("singleCharA = %c", singleCharA);

	// 改行する
	printf_s("\n");

	// 覚えておいたsingleCharBを画面に表示
	printf_s("singleCharB = %c", singleCharB);

	return 0;
}
