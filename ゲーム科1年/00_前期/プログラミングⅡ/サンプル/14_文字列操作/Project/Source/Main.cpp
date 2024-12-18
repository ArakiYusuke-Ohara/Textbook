#include <stdio.h>
#include <string.h>

int main(void)
{
	char strA[32] = { 0 };
	char strB[32] = "コピーしたい文字列";

	// strcpyは文字列をコピーする関数
	strcpy_s(strA, strB);

	printf_s("strA = %s\n", strA);

	return 0;
}

int main(void)
{
	char str[32];

	// scanf_sで文字列を入力する場合は、
	// 文字列の配列の要素数を渡す必要がある
	printf_s("文字列を入力（半角32文字まで）\n");
	scanf_s("%s", str, 32);

	// strcmpは文字列が一致するかチェックする関数
	// 文字列が完全に一致すると0が返却される
	if (strcmp(str, "yamada") == 0)
	{
		printf_s("入力した文字列が yamada と完全一致しました\n");
	}
	else
	{
		printf_s("入力した文字列が yamada と一致しませんでした\n");
	}

	return 0;
}

int main(void)
{
	char strA[32] = "yamada";
	char strB[32] = "tarou";

	// strAの末尾に半角スペースを結合
	strcat_s(strA, " ");

	// strAの末尾にstrBを結合
	strcat_s(strA, strB);

	printf_s("%s\n", strA);

	return 0;
}

int main(void)
{
	char strA[32] = "yamada";
	char strB[32] = "tarou";

	// sprintf_sはprintfの要領で文字列を設定できる
	sprintf_s(strA, "%s %s", strA, strB);

	printf_s("%s\n", strA);

	return 0;
}
