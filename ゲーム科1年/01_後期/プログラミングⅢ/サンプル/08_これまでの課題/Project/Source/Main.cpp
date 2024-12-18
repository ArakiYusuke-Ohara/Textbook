#include <iostream>
#include "Enemy/Enemy.h"

#define ENEMY_MAX 3

using namespace std;

int main()
{
	Enemy* enemy = new Enemy[ENEMY_MAX];
	int enemyPosX = 0;
	int enemyPosY = 0;


	for (int i = 0; i < ENEMY_MAX; i++)
	{
		cout << "エネミーのX座標を入力" << endl;
		cin >> enemyPosX;
		cout << "エネミーのY座標を入力" << endl;
		cin >> enemyPosY;

		enemy[i].SetPos(enemyPosX, enemyPosY);
	}

	int enemyIndex = 0;

	while (1)
	{
		cout << "座標が知りたいエネミーの添え字を入力（-1で終了）" << endl;
		cin >> enemyIndex;

		// -1入力で終了
		if (enemyIndex == -1)
		{
			break;
		}

		// 配列の範囲外を入力すると打ち直し
		if (enemyIndex < 0 || enemyIndex >= ENEMY_MAX)
		{
			cout << "エネミーが存在しない添え字です" << endl;
			continue;
		}

		// 座標を描画する
		enemy[enemyIndex].DrawPos();
	}

	delete[] enemy;

	return 0;
}
