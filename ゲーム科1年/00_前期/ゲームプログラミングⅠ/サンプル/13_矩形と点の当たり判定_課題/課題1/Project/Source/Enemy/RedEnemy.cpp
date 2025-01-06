#include "DxLib.h"
#include "RedEnemy.h"

// •Ï”
RedEnemyData g_RedEnemyData[RED_ENEMY_MAX] = {0};

void InitRedEnemy()
{
	for (int i = 0; i < RED_ENEMY_MAX; i++)
	{
		g_RedEnemyData[i].handle = LoadGraph("Data/Enemy/RedEnemy.png");

		g_RedEnemyData[i].posX = 1200.0f - i * 300.0f;
		g_RedEnemyData[i].posY = 200.0f + i * 200.0f;
		g_RedEnemyData[i].moveX = 0.0f;
		g_RedEnemyData[i].moveY = 0.0f;
	}
}

void UpdateRedEnemy()
{
	for (int i = 0; i < RED_ENEMY_MAX; i++)
	{
		g_RedEnemyData[i].hitFlag = false;
	}
}

void DrawRedEnemy()
{
	for (int i = 0; i < RED_ENEMY_MAX; i++)
	{
		DrawGraph((int)g_RedEnemyData[i].posX, (int)g_RedEnemyData[i].posY, g_RedEnemyData[i].handle, TRUE);

		if (g_RedEnemyData[i].hitFlag)
		{
			DrawFormatString(0, 40, GetColor(255, 255, 255), "RedEnemy[%d]:ƒ}ƒEƒX‚ª“–‚½‚Á‚½", i);
		}
	}
}

void FinRedEnemy()
{
	for (int i = 0; i < RED_ENEMY_MAX; i++)
	{
		DeleteGraph(g_RedEnemyData[i].handle);
	}
}

RedEnemyData* GetRedEnemy()
{
	return g_RedEnemyData;
}
