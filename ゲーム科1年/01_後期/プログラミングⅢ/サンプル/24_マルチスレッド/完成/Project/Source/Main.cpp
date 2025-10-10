#include <iostream>
#include <thread>

void FunctionA();
void FunctionB();

int main()
{
	std::thread threadA(FunctionA); // FunctionAを別スレッドで実行
	std::thread threadB(FunctionB); // FunctionBを別スレッドで実行

	threadA.join(); // threadAの終了を待つ
	threadB.join(); // threadBの終了を待つ

	// 何かキーを押したら終了
	std::cin.get();

	return 0;
}

void FunctionA()
{
	// FunctionAと10回表示する
	for (int i = 0; i < 10; i++)
	{
		std::cout << "FunctionA" << std::endl;
	}
}

void FunctionB()
{
	// FunctionBと10回表示する
	for (int i = 0; i < 10; i++)
	{
		std::cout << "FunctionB" << std::endl;
	}
}

