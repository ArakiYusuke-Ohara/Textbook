#pragma once

// プレイヤーサイズ
#define BLUE_ENEMY_WIDTH	(128)
#define BLUE_ENEMY_HEIGHT	(256)

struct BlueEnemyData
{
	bool hitFlg;
	int handle;
	float posX;
	float posY;
	float moveX;
	float moveY;
};

// 関数のプロトタイプ宣言
void InitBlueEnemy();
void UpdateBlueEnemy();
void DrawBlueEnemy();
void FinBlueEnemy();

BlueEnemyData* GetBuleEnemyData();
