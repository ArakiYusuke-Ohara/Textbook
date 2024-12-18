#include "EnemyManager.h"
#include "SightMachine.h"

int g_EnemySpawnTimer = 0;

void InitEnemy()
{
	// エネミー出現タイマーを初期化
	g_EnemySpawnTimer = 0;

	// SightMachine初期化
	InitSightMachine();
}

void LoadEnemy()
{
	// 各エネミーをロード

	// SightMachineロード
	LoadSightMachine();
}

void StartEnemy()
{
	// 各エネミーを開始

	// SightMachineロード
	StartSightMachine();
}

void StepEnemy()
{
	// 各エネミーをステップ

	// SightMachineステップ
	StepSightMachine();
}

void UpdateEnemy()
{
	// 各エネミーを更新

	// SightMachine更新
	UpdateSightMachine();
}

void DrawEnemy()
{
	// 各エネミーを描画

	// SightMachine描画
	DrawSightMachine();
}

void FinEnemy()
{
	// 各エネミーを終了

	// SightMachine終了
	FinSightMachine();
}
