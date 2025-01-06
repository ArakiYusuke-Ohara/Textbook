#include "DxLib.h"
#include "BlueEnemy.h"

// ïœêî
BlueEnemyData g_BlueEnemyData = { 0 };

void InitBlueEnemy()
{
	g_BlueEnemyData.handle = LoadGraph("Data/Enemy/BlueEnemy.png");

	g_BlueEnemyData.posX = 400.0f;
	g_BlueEnemyData.posY = 600.0f;
	g_BlueEnemyData.moveX = 0.0f;
	g_BlueEnemyData.moveY = 0.0f;
}

void UpdateBlueEnemy()
{
}

void DrawBlueEnemy()
{
	DrawGraph((int)g_BlueEnemyData.posX, (int)g_BlueEnemyData.posY, g_BlueEnemyData.handle, TRUE);
}

void FinBlueEnemy()
{
}
