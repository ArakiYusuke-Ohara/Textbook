#include <string>
#include <iostream>

using namespace std;

int main()
{
	// 文字列クラスstring
	std::string name = "大原　太郎";
	cout << name << endl;

	// 足し算で連結できる
	std::string last = "Ohara";
	std::string first = "Taro";
	name = last + " " + first;
	cout << name << endl;

	// size関数で文字数取得
	cout << "文字数：" << name.size() << endl;

	// 添え字で１文字アクセスできる
	cout << "name[2]：" << name[2] << endl;

	// 比較も簡単
	std::string nameA = "Ohara";
	std::string nameB = "Ohara";
	if (nameA == nameB)
	{
		cout << "nameAとnameBは同じ" << endl;
	}

	return 0;
}

