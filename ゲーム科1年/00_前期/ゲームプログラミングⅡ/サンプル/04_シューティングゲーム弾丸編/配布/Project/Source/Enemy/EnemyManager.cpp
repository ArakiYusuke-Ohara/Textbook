#include "EnemyManager.h"
#include "Flies.h"
#include "DragonFly.h"
#include "Kapu.h"


// 出現したすべての敵データを見ることができる配列
EnemyBaseData* g_AllEnemyData[ENEMY_MAX];

// 出現した敵カウンター
int g_EnemyCount = 0;

void InitEnemy()
{
	g_EnemyCount = 0;

	// 各エネミーを初期化
	// Flies
	InitFlies();
	// DragonFly
	InitDragonFly();
	// Kapu
	InitKapu();
}

void LoadEnemy()
{
	// 各エネミーをロード
	// Flies
	LoadFlies();
	// DragonFly
	LoadDragonFly();
	// Kapu
	LoadKapu();
}

void StepEnemy()
{
	// 各エネミーをステップ
	// Flies
	StepFlies();
	// DragonFly
	StepDragonFly();
	// Kapu
	StepKapu();
}

void UpdateEnemy()
{
	// 各エネミーを更新
	// Flies
	UpdateFlies();
	// DragonFly
	UpdateDragonFly();
	// Kapu
	UpdateKapu();
}

void DrawEnemy()
{
	// 各エネミーを描画
	// Flies
	DrawFlies();
	// DragonFly
	DrawDragonFly();
	// Kapu
	DrawKapu();
}

void FinEnemy()
{
	// 各エネミーを終了
	// Flies
	FinFlies();
	// DragonFly
	FinDragonFly();
	// Kapu
	FinKapu();
}

EnemyBaseData** GetEnemy()
{
	return g_AllEnemyData;
}

void SpawnEnemy(EnemyType type, float posX, float posY)
{
	// 配置した敵をこの変数に入れる
	EnemyBaseData* spawnEnemy = nullptr;

	// タイプごとに敵を生成して配置
	switch (type)
	{
	case ENEMY_TYPE_FLIES:
		spawnEnemy = SpawnFlies(posX, posY);
		break;

	case ENEMY_TYPE_DRAGON_FLY:
		spawnEnemy = SpawnDragonFly(posX, posY);
		break;

	case ENEMY_TYPE_KAPU:
		spawnEnemy = SpawnKapu(posX, posY);
		break;
	}

	// 無事に配置出来たら登録
	if (spawnEnemy && g_EnemyCount < ENEMY_MAX)
	{
		g_AllEnemyData[g_EnemyCount] = spawnEnemy;
		g_EnemyCount++;
	}
}

