#include <stdio.h>

//int main(void)
//{
//	// int型の変数
//	int num = 0;
//
//	// intポインタ型の変数
//	int* pointer;
//
//	// ポインタ変数には型に合わせた参照（アドレス）を格納できる
//	// 変数の参照は&をつけることで指定できる
//	pointer = &num;
//
//	printf_s("変数numのアドレスは%x番地\n", pointer);
//
//	return 0;
//}

int main(void)
{
	// int型の変数
	int num = 0;

	// intポインタ型の変数
	int* pointer = &num;

	// pointerが参照している変数を書き換える
	*pointer = 100;

	// pointerを通じてnumが書き換わっている
	printf_s("num = %d", num);

	return 0;
}
