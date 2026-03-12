#include <list>
#include <iostream>

using namespace std;

int main()
{
	auto autoInt = 100;
	auto autoFloat = 34.5f;
	auto autoDouble = 1.23;
	auto autoChar = 'a';

	// auto型で宣言した変数の値
	cout << "autoInt：" << autoInt << endl;
	cout << "autoFloat：" << autoFloat << endl;
	cout << "autoDouble：" << autoDouble << endl;
	cout << "autoChar：" << autoChar << endl;

	cout << endl;

	// auto型で宣言した変数のサイズ
	cout << "autoIntのサイズ：" << sizeof(autoInt) << "Byte" << endl;
	cout << "autoFloatのサイズ：" << sizeof(autoFloat) << "Byte" << endl;
	cout << "autoDoubleのサイズ：" << sizeof(autoDouble) << "Byte" << endl;
	cout << "autoCharのサイズ：" << sizeof(autoChar) << "Byte" << endl;

	// auto型はイテレータのように宣言の長い変数に使うと効果的
	std::list<int> testList;
	auto itr = testList.begin();

	return 0;
}


