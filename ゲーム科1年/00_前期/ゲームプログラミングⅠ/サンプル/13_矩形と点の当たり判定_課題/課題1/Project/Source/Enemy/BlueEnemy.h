#pragma once

#define BLUE_ENEMY_WIDTH (128)
#define BLUE_ENEMY_HEIGHT (256)

struct BlueEnemyData
{
	int handle;
	float posX;
	float posY;
	float moveX;
	float moveY;
	bool hitFlag;
};

// 関数のプロトタイプ宣言
void InitBlueEnemy();
void UpdateBlueEnemy();
void DrawBlueEnemy();
void FinBlueEnemy();

// 青エネミー取得
BlueEnemyData* GetBlueEnemy();
