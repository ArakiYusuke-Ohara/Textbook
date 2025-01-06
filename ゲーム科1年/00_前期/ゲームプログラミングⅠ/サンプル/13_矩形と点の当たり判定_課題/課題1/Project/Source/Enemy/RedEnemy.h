#pragma once

#define RED_ENEMY_MAX 3
#define RED_ENEMY_WIDTH 128
#define RED_ENEMY_HEIGHT 64

// 関数のプロトタイプ宣言
void InitRedEnemy();
void UpdateRedEnemy();
void DrawRedEnemy();
void FinRedEnemy();

struct RedEnemyData
{
	int handle;
	float posX;
	float posY;
	float moveX;
	float moveY;
	bool hitFlag;
};

// 赤エネミー取得
RedEnemyData* GetRedEnemy();
