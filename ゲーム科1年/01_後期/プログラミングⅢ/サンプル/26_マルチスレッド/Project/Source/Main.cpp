
#include <thread>
#include <iostream>
#include <chrono>

using namespace std;

void SubA();
void SubB();

// メイン関数
int main()
{
	// スレッド開始
	std::thread tA(SubA);
	std::thread tB(SubB);

	// Mainと5回表示
	for (int i = 0; i < 5; i++)
	{
		cout << "Main\n";
		// 1秒停止
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	// メインスレッドが先に終了してはいけない
	// join関数で必ず終了待ちをすること
	tA.join();
	tB.join();
	cout << "全部終わった" << endl;

	// 全部終わってからメインスレッド終了
	return 0;
}

// サブ関数A
void SubA()
{
	// SubAと5回表示
	for (int i = 0; i < 5; i++)
	{
		cout << "SubA\n";
		// 1秒停止
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

// サブ関数B
void SubB()
{
	// SubBと5回表示
	for (int i = 0; i < 5; i++)
	{
		cout << "SubB\n";
		// 1秒停止
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

#if 0

#include <thread>
#include <iostream>

using namespace std;

void sub();

// メイン関数
int main()
{
	cout << "Main関数" << endl;

	// スレッドを開始
	std::thread t(sub);

	// スレッド終了待ち
	t.join();

	return 0;
}

// サブ関数
void sub()
{
	cout << "Sub関数" << endl;
}

#include <thread>
#include <iostream>
#include <chrono>

using namespace std;

void SubA();
void SubB();

// メイン関数
int main()
{
	// スレッド開始
	std::thread tA(SubA);
	std::thread tB(SubB);

	// Mainと5回表示
	for (int i = 0; i < 5; i++)
	{
		cout << "Main\n";
		// 1秒停止
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	// メインスレッドが先に終了してはいけない
	// join関数で必ず終了待ちをすること
	tA.join();
	tB.join();
	cout << "全部終わった" << endl;

	// 全部終わってからメインスレッド終了
	return 0;
}

// サブ関数A
void SubA()
{
	// SubAと5回表示
	for (int i = 0; i < 5; i++)
	{
		cout << "SubA\n";
		// 1秒停止
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

// サブ関数B
void SubB()
{
	// SubBと5回表示
	for (int i = 0; i < 5; i++)
	{
		cout << "SubB\n";
		// 1秒停止
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

#include <thread>
#include <iostream>

using namespace std;

void SubA();
void SubB();

// メイン関数
int main()
{
	// スレッド開始
	std::thread tA(SubA);
	std::thread tB(SubB);

	// Mainと100回表示
	for (int i = 0; i < 100; i++)
	{
		cout << "Main\n";
	}

	// スレッド終了待ち
	tA.join();
	tB.join();

	cout << "全部終わった" << endl;

	return 0;
}

// サブ関数A
void SubA()
{
	// SubAと100回表示
	for (int i = 0; i < 100; i++)
	{
		cout << "SubA\n";
	}
}

// サブ関数B
void SubB()
{
	// SubBと100回表示
	for (int i = 0; i < 100; i++)
	{
		cout << "SubB\n";
	}
}



#endif
