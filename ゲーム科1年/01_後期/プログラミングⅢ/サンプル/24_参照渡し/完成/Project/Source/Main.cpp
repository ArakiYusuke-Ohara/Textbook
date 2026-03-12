#include "Enemy/Enemy.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	Enemy enemies[100];

	// クラスや構造体などの大きなデータは
	// コピーよりも参照渡しの方が速い
	for (Enemy& enemy : enemies)
	{
		enemy.Init();
	}
}


#if 0

#include <iostream>

using namespace std;

int main()
{
	// 変数number
	int number = 10;

	// 変数numberを参照するref（参照渡し）
	int& ref = number;

	// refはnumberを参照しているのでnumberが100になる
	ref = 100;
	cout << "number：" << number << endl;

	return 0;
}

#include <iostream>

using namespace std;

// 引数の値を入れ替える関数
// 戻り値だけでは対応できない場合は参照渡しが使える
void Swap(int& a, int& b)
{
	// aを退避
	int w = a;

	// 引数が参照渡しなので元々の変数が書き変わる
	a = b;
	b = w;
}

int main()
{
	int x = 5;
	int y = 20;

	// ２つの値を入れ替える
	Swap(x, y);

	cout << "x：" << x << endl;
	cout << "y：" << y << endl;

	return 0;
}

#endif