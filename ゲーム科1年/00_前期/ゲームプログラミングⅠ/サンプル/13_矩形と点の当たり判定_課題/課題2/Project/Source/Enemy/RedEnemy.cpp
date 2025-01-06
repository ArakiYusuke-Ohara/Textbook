#include "DxLib.h"
#include "RedEnemy.h"

// ïœêî
RedEnemyData g_RedEnemyData[RED_ENEMY_NUM] = {0};

void InitRedEnemy()
{
	const float DEFAULT_POS_X[RED_ENEMY_NUM] =
	{
		1200.0f,
		400.0f,
		750.0f
	};

	const float DEFAULT_POS_Y[RED_ENEMY_NUM] =
	{
		200.0f,
		500.0f,
		350.0f
	};

	for (int i = 0; i < RED_ENEMY_NUM; i++)
	{
		g_RedEnemyData[i].handle = LoadGraph("Data/Enemy/RedEnemy.png");

		g_RedEnemyData[i].posX = DEFAULT_POS_X[i];
		g_RedEnemyData[i].posY = DEFAULT_POS_Y[i];
		g_RedEnemyData[i].moveX = 0.0f;
		g_RedEnemyData[i].moveY = 0.0f;
	}
}

void UpdateRedEnemy()
{
	for (int i = 0; i < RED_ENEMY_NUM; i++)
	{
		g_RedEnemyData[i].hitFlag = false;
	}
}

void DrawRedEnemy()
{
	for (int i = 0; i < RED_ENEMY_NUM; i++)
	{
		DrawGraph((int)g_RedEnemyData[i].posX, (int)g_RedEnemyData[i].posY, g_RedEnemyData[i].handle, TRUE);

		if (g_RedEnemyData[i].hitFlag)
		{
			DrawString(0, 40, "RedEnemy:É}ÉEÉXÇ™ìñÇΩÇ¡ÇΩ", GetColor(255, 255, 255));
		}
	}
}

void FinRedEnemy()
{
	for (int i = 0; i < RED_ENEMY_NUM; i++)
	{
		DeleteGraph(g_RedEnemyData[i].handle);
	}
}

RedEnemyData* GetRedEnemies()
{
	return g_RedEnemyData;
}
