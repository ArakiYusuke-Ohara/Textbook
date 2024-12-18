#pragma once

#define WATER_ENEMY_NUM		(3)
#define WATER_ENEMY_RADIUS	(128.0f)
#define WATER_ENEMY_WIDTH	(256.0f)
#define WATER_ENEMY_HEIGHT	(256.0f)

struct WaterEnemyData
{
	int handle;
	float posX;
	float posY;
	float moveX;
	float moveY;
	bool hitFlag;
};

// 関数のプロトタイプ宣言
void InitWaterEnemy();
void StepWaterEnemy();
void UpdateWaterEnemy();
void DrawWaterEnemy();
void FinWaterEnemy();

// 水色エネミー取得
WaterEnemyData* GetWaterEnemies();

// 当たり判定
void HitWaterEnemy(int index);
