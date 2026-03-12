#include <list>
#include <iostream>

int main()
{
	// 動的配列vectorを生成
	std::list <int> testList;

	// リストの末尾に要素を追加
	testList.push_back(1);
	testList.push_back(2);
	testList.push_back(3);
	testList.push_back(4);
	testList.push_back(5);

	// リストは配列と違い添え字でアクセスできない
	// 代わりにアクセス用クラスであるイテレータを使う
	// begin関数はリストの先頭を参照するイテレータを返す
	std::list<int>::iterator itr = testList.begin();

	// イテレータを1つ進める
	itr++;

	// イテレータが参照している要素を削除する
	testList.erase(itr);

	// 件数を取得
	int size = testList.size();

	// 件数表示
	std::cout << "配列の件数は" << size << "件です" << std::endl;

	int count = 0;
	// イテレータを使ってfor文を回すときはこのように書く
	for (itr = testList.begin(); itr != testList.end(); itr++)
	{
		std::cout << "testList[" << count << "] = " << *itr << std::endl;
		count++;
	}

	return 0;
}


