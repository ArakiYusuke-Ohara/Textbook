#include <stdio.h>

int main(void)
{
	// float型の配列
	float num[10] = { 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f, 4.5f, 5.0f, 5.5f };

	// floatポインタ型の変数
	// 配列は添字を書かなければ先頭アドレス（0番目のアドレス）となる
	float* pointer = num;

	// 配列numの先頭アドレスを表示
	printf_s("配列numのアドレスは%x番地\n", pointer);

	return 0;
}

int main(void)
{
	// float型の配列
	float num[5] = { 1.0f, 1.5f, 2.0f, 2.5f, 3.0f };

	// 先頭アドレスを設定
	float* pointer = num;

	// ポインタを足し算すると、その分だけ示している位置が右にずれる
	// この場合3つ分右にずれる
	pointer += 3;

	// ポインターが示している要素を表示
	printf_s("pointerが示しているのは%f\n", *pointer);

	return 0;
}

int main(void)
{
	// float型の配列
	float num[5] = { 1.0f, 1.5f, 2.0f, 2.5f, 3.0f };

	// 先頭アドレスを設定
	float* pointer = num;

	for (int i = 0; i < 5; i++)
	{
		// ポインターが示している要素を表示
		printf_s("pointerが示しているのは%f\n", *pointer);

		// インクリメントは1加算する
		// ポインターの場合は右に1つずれる
		pointer++;
	}

	return 0;
}
