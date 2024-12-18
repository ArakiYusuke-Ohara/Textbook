#include "DxLib.h"
#include "WaterEnemy.h"

// 変数
WaterEnemyData g_WaterEnemyData[WATER_ENEMY_NUM] = {0};

void InitWaterEnemy()
{
	const float DEFAULT_POS_X[] =
	{
		1200.0f,
		400.0f,
		750.0f
	};

	const float DEFAULT_POS_Y[] =
	{
		200.0f,
		500.0f,
		350.0f
	};

	for (int i = 0; i < WATER_ENEMY_NUM; i++)
	{
		g_WaterEnemyData[i].handle = LoadGraph("Resource/Enemy/WaterEnemy.png");

		g_WaterEnemyData[i].posX = DEFAULT_POS_X[i];
		g_WaterEnemyData[i].posY = DEFAULT_POS_Y[i];
		g_WaterEnemyData[i].moveX = 0.0f;
		g_WaterEnemyData[i].moveY = 0.0f;
	}
}

void StepWaterEnemy()
{
	for (int i = 0; i < WATER_ENEMY_NUM; i++)
	{
		// ヒットフラグをリセット
		g_WaterEnemyData[i].hitFlag = false;
	}
}

void UpdateWaterEnemy()
{
}

void DrawWaterEnemy()
{
	for (int i = 0; i < WATER_ENEMY_NUM; i++)
	{
		DrawGraph((int)g_WaterEnemyData[i].posX, (int)g_WaterEnemyData[i].posY, g_WaterEnemyData[i].handle, TRUE);

		if (g_WaterEnemyData[i].hitFlag)
		{
			DrawString(0, 0, "マウスが当たった！！", GetColor(255, 255, 255));
		}
	}
}

void FinWaterEnemy()
{
	for (int i = 0; i < WATER_ENEMY_NUM; i++)
	{
		DeleteGraph(g_WaterEnemyData[i].handle);
	}
}

WaterEnemyData* GetWaterEnemies()
{
	return g_WaterEnemyData;
}

void HitWaterEnemy(int index)
{
	g_WaterEnemyData[index].hitFlag = true;
}
