#include <stdio.h>
#include <stdlib.h>

struct EnemyData
{
	bool isActive;
	int handle;
	float posX;
	float posY;
	float moveX;
	float moveY;
	float width;
	float height;
};

// 各ステージの敵の最大数
const int ENEMY_MAX[] =
{
	10,	// ステージ1は10体
	30,	// ステージ2は30体
	5,	// ステージ3は5体
};

// 動的メモリはポインタで管理する
EnemyData* g_Enemies = NULL;

int main(void)
{
	// ステージ番号
	int stageNumber = 2;

	// そのステージに何体の敵が出てくるか
	int enemyNum = ENEMY_MAX[stageNumber];

	// callocで出てくる敵の数だけメモリを確保できる
	g_Enemies = (EnemyData*)calloc(enemyNum, sizeof(EnemyData));

	// callocが失敗する可能性は考えておく
	if (g_Enemies == NULL)
	{
		return -1;
	}

	// まずは敵1体分の容量を表示してみる
	printf_s("敵1体分の容量は %zu バイトです\n", sizeof(EnemyData));

	// 敵の配列が全部で何バイトか表示してみる
	printf_s("ステージ%dのg_Enemiesの容量は %zu バイトです\n", 
		stageNumber + 1, enemyNum * sizeof(EnemyData));

	// 確保さえすれば配列と使い方は同じ
	EnemyData* enemy = g_Enemies;
	for (int i = 0; i < enemyNum; i++, enemy++)
	{
		enemy->posX = i * 10.0f;
		enemy->posY = i * 20.0f;
		printf_s("%d番目の敵の座標は（%.2f, %.2f）\n", i, enemy->posX, enemy->posY);
	}

	// callocした配列は使い終わったら必ずfreeする
	// 忘れるとメモリリークが発生する
	// またfreeしたら必ずポインタ変数にNULLを入れること
	free(g_Enemies);
	g_Enemies = NULL;

	return 0;
}

#if 0
#define ENEMY_MAX (30)

EnemyData g_Enemies[ENEMY_MAX];

int main(void)
{
	// sizeofでカッコ内を容量を取得できる
	int enemyDataSize = sizeof(g_Enemies);

	// まずは敵1体分の容量を表示してみる
	// sizeofは型名でも使用することができる
	printf_s("敵1体分の容量は %zu バイトです\n", (int)sizeof(EnemyData));

	// 敵の配列が全部で何バイトか表示してみる
	printf_s("g_Enemiesの容量は %zu バイトです\n", enemyDataSize);

	return 0;
}


#endif
