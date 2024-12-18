#pragma once

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
};
