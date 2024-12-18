#pragma once

#define RED_ENEMY_NUM		(3)
#define RED_ENEMY_WIDTH		(128.0f)
#define RED_ENEMY_HEIGHT	(64.0f)

struct RedEnemyData
{
	int handle;
	float posX;
	float posY;
	float moveX;
	float moveY;
	bool hitFlag;
};

// 関数のプロトタイプ宣言
void InitRedEnemy();
void UpdateRedEnemy();
void DrawRedEnemy();
void FinRedEnemy();

RedEnemyData* GetRedEnemies();
