#include <random>
#include <iostream>

using namespace std;

//// メルセンヌ・ツイスタークラスを使った乱数
//int main()
//{
//	mt19937 mt;
//
//	for (int i = 0; i < 10; i++)
//	{
//		cout << mt() << endl;
//	}
//
//	return 0;
//}

//// ランダムデバイスクラスを使った乱数
//int main()
//{
//	random_device rd;
//
//	for (int i = 0; i < 10; i++)
//	{
//		cout << rd() << endl;
//	}
//
//	return 0;
//}

// メルセンヌ・ツイスター法のシード設定
//int main()
//{
//	random_device rd;
//
//	// 完全な乱数であるランダムデバイス乱数でシードを設定する
//	mt19937 mt(rd());
//
//	for (int i = 0; i < 10; i++)
//	{
//		cout << mt() << endl;
//	}
//
//	return 0;
//}

//// 離散一様分布(int)
//int main()
//{
//	random_device rd;
//	// 分布を使用する場合はランダムエンジンが必要
//	default_random_engine randomEngine(rd());
//
//	// 0～9を等確率で発生させる
//	uniform_int_distribution<int> dist(0, 9);
//	for (int i = 0; i < 100; i++)
//	{
//		cout << dist(randomEngine) << endl;
//	}
//
//	return 0;
//}

//// 離散一様分布(float)
int main()
{
	random_device rd;
	// 分布を使用する場合はランダムエンジンが必要
	default_random_engine randomEngine(rd());

	// 0.0～1.0を等確率で発生させる
	uniform_real_distribution<float> dist(0.0, 1.0);
	for (int i = 0; i < 100; i++)
	{
		cout << dist(randomEngine) << endl;
	}

	return 0;
}
