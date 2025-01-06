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
	g_BlueEnemyData.hitFlag = false;
}

void DrawBlueEnemy()
{
	DrawGraph((int)g_BlueEnemyData.posX, (int)g_BlueEnemyData.posY, g_BlueEnemyData.handle, TRUE);

	if (g_BlueEnemyData.hitFlag)
	{
		DrawString(0, 20, "BlueEnemy:É}ÉEÉXÇ™ìñÇΩÇ¡ÇΩ", GetColor(255, 255, 255));
	}
}

void FinBlueEnemy()
{
	DeleteGraph(g_BlueEnemyData.handle);
}

BlueEnemyData* GetBlueEnemy()
{
	return &g_BlueEnemyData;
}
