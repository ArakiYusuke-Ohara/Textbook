#include <array>
#include <iostream>

using namespace std;

int main()
{
	// int型5個分の配列
	std::array<int, 5> testArray = {1, 2, 3, 4, 5};

	// 使い方はC言語配列と一緒
	testArray[2] = 30;

	// 同じ型と件数のarrayであればコピーできる
	std::array<int, 5> copyArray = testArray;

	// メンバ関数sizeで件数を取得できる
	int size = testArray.size();
	cout << "testArrayの件数：" << size << endl;

	// 範囲for文で全要素を回せる　
	int total = 0;
	for (int num : testArray)
	{
		total += num;
	}
	cout << "合計：" << total << endl;

	return 0;
}


