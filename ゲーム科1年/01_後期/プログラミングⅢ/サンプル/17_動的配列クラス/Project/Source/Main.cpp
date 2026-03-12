#include <vector>
#include <iostream>

int main()
{
	// 動的配列vectorを生成
	std::vector<int> testVector;

	// 配列の末尾に要素を追加
	testVector.push_back(1);
	testVector.push_back(2);
	testVector.push_back(3);

	// 配列の末尾の要素を削除
	testVector.pop_back();

	// 配列の末尾に要素を追加
	testVector.push_back(4);
	testVector.push_back(5);

	// 件数を取得
	int size = testVector.size();

	// コンソール表示
	std::cout << "配列の件数は" << size << "件です" << std::endl;

	// 普通の配列通りにfor文で回せる
	for (int i = 0; i < size; i++)
	{
		std::cout << "testVector[" << i << "] = " << testVector[i] << std::endl;
	}

	return 0;
}


