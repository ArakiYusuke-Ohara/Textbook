#include <stdio.h>

void FunctionA();
void FunctionB();

// どの関数でも共通で使えるグローバル変数
int g_Total = 0;

int main(void)
{
	// この変数はmain関数のローカル変数
	int numA = 1;
	int numB = 2;

	g_Total += (numA + numB);

	FunctionA();
	FunctionB();

	printf_s("g_Total = %d\n", g_Total);

	return 0;
}

void FunctionA()
{
	// この変数はFunctionA関数のローカル変数
	// main関数とは名前は同じだが別物
	int numA = 10;
	int numB = 20;

	g_Total += (numA + numB);
}

void FunctionB()
{
	// この変数はFunctionB関数のローカル変数
	// 他の関数とは名前は同じだが別物
	int numA = 100;
	int numB = 200;

	g_Total += (numA + numB);
}
