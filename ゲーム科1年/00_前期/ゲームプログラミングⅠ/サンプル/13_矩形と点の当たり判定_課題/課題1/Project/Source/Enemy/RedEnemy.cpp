#include "DxLib.h"
#include "RedEnemy.h"

// ïœêî
RedEnemyData g_RedEnemyData = { 0 };

void InitRedEnemy()
{
	g_RedEnemyData.handle = LoadGraph("Data/Enemy/RedEnemy.png");

	g_RedEnemyData.posX = 1200.0f;
	g_RedEnemyData.posY = 200.0f;
	g_RedEnemyData.moveX = 0.0f;
	g_RedEnemyData.moveY = 0.0f;
}

void UpdateRedEnemy()
{
}

void DrawRedEnemy()
{
	DrawGraph((int)g_RedEnemyData.posX, (int)g_RedEnemyData.posY, g_RedEnemyData.handle, TRUE);
}

void FinRedEnemy()
{
}
