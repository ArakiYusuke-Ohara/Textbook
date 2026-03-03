#include <stdio.h>

int main(void)
{
	// 変数
	int numberList[3] = { 5, 7, 3 };

	// ポインタ変数
	int* pt = numberList;

	// ポインタ変数は参照先を書き換えられる
	*pt = 50;
	*pt += 20;

	// constポインタ変数
	const int* constPt = numberList;

	// constポインタ変数は参照先がconstでなくても変えられない
	//*constPt = 100;

	// ポインタ自身はずらせる
	constPt += 2;

	return 0;
}

#if 0

int main(void)
{
	// constを頭に書くと定数
	const float DEFAULT_POS_X = 300.0f;
	const float DEFAULT_POS_Y = 400.0f;

	// 定数は変更できない
	//DEFAULT_POS_X = 200.0f;
	//DEFAULT_POS_Y -= 50.0f;

	// 変数
	float posX = DEFAULT_POS_X;
	float posY = DEFAULT_POS_Y;

	// 変数は変更できる
	posX += 30.0f;
	posY -= 10.0f;

	return 0;
}


struct PlayerData
{
	int hp;		// HP
	int attack;	// 攻撃力
};

struct EnemyData
{
	int hp;		// HP
	int attack;	// 攻撃力
};

// プレイヤーから敵へのダメージ
void DamageFromPlayerToEnemy(const PlayerData* player, EnemyData* enemy);

// 敵からプレイヤーへのダメージ
void DamageFromEnemyToPlayer(PlayerData* player, const EnemyData* enemy);

int main(void)
{
	PlayerData player = { 10, 2 };
	EnemyData enemy = { 15, 1 };

	DamageFromPlayerToEnemy(&player, &enemy);
	DamageFromEnemyToPlayer(&player, &enemy);

	printf_s("プレイヤーのHP：%d\n", player.hp);
	printf_s("敵のHP：%d\n", enemy.hp);

	return 0;
}

// 間違ってもPlayerDataが変わらないようにconst
void DamageFromPlayerToEnemy(const PlayerData* player, EnemyData* enemy)
{
	// 敵のHP減少
	enemy->hp -= player->attack;
}

// 間違ってもEnemyDataが変わらないようにconst
void DamageFromEnemyToPlayer(PlayerData* player, const EnemyData* enemy)
{
	// プレイヤーのHP減少
	player->hp -= enemy->attack;
}

#endif
