#include "EnemyManager.h"
#include "Flies.h"
#include "DragonFly.h"

void InitEnemy()
{
	// 各エネミーを初期化
	// Flies
	InitFlies();
	// DragonFly
	InitDragonFly();
}

void LoadEnemy()
{
	// 各エネミーをロード
	// Flies
	LoadFlies();
	// DragonFly
	LoadDragonFly();
}

void StartEnemy()
{
	// Flies
	StartFlies();
	// DragonFly
	StartDragonFly();
}

void StepEnemy()
{
	// 各エネミーをステップ
	// Flies
	StepFlies();
	// DragonFly
	StepDragonFly();
}

void UpdateEnemy()
{
	// 各エネミーを更新
	// Flies
	UpdateFlies();
	// DragonFly
	UpdateDragonFly();
}

void DrawEnemy()
{
	// 各エネミーを描画
	// Flies
	DrawFlies();
	// DragonFly
	DrawDragonFly();
}

void FinEnemy()
{
	// 各エネミーを終了
	// Flies
	FinFlies();
	// DragonFly
	FinDragonFly();
}

