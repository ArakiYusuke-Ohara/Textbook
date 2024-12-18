#include <stdio.h>

//int main(void)
//{
//	// short int型は16ビットで範囲は-32768～32767
//	short int shortIntNumber = 0;
//
//	// long int型は32ビットで範囲は-2147483648～2147483647
//	// long int と int は同じ
//	long int longIntNumber = 0;
//
//	// long long int型は64ビットで範囲は-9223372036854775808～9223372036854775807
//	long long int longLongIntNumber = 9223372036854775807;
//
//	printf_s("short int = %d\n", shortIntNumber);
//	printf_s("long  int = %d\n", longIntNumber);
//	printf_s("long long int = %lld\n", longLongIntNumber);
//
//	return 0;
//}

//int main(void)
//{
//	// 整数型はunsignedをつけることで負数を使えなくする代わりに
//	// 正数を範囲を広げることができる
//
//	// unsigned short int型は16ビットで範囲は0～65535
//	unsigned short int shortIntNumber = 65535;
//
//	// unsigned long int型は32ビットで範囲は0～4294967295
//	// long int と int は同じ
//	unsigned long int longIntNumber = 4294967295;
//
//	// unsigned long long int型は64ビットで範囲は0～18446744073709551615
//	unsigned long long int longLongIntNumber = 18446744073709551615;
//
//	printf_s("short int = %u\n", shortIntNumber);
//	printf_s("long  int = %u\n", longIntNumber);
//	printf_s("long long int = %llu\n", longLongIntNumber);
//
//	return 0;
//}

int main(void)
{
	// 文字を使いたいときはchar型を使う
	// ただし半角英数字記号1文字しか格納できない
	char character = 'a';

	// 小数を使うときはfloat型もしくはdouble型を使う
	float floatPi = 3.14159265f;			// float型は32ビット
	float doublePi = 3.1415926535897932;	// double型は64ビット

	printf_s("char = %c\n", character);
	printf_s("float = %f\n", floatPi);
	printf_s("double = %lf\n", doublePi);

	return 0;
}
